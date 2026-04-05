#include "networkmanager.h"

#include <stdexcept>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/thread/future.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

NetworkResponse NetworkManager::request(const std::string &host,
                                        const std::string &path,
                                        const std::string &method,
                                        const std::string &body,
                                        const std::map<std::string, std::string> &headers)
{
    try {
        net::io_context ioc;
        ssl::context ctx(ssl::context::tlsv12_client);
        ctx.set_default_verify_paths();

        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
            throw std::runtime_error("SSL SNI failed");

        auto results = tcp::resolver(ioc).resolve(host, "443");
        beast::get_lowest_layer(stream).connect(results);
        stream.handshake(ssl::stream_base::client);

        http::verb verb;
        if (method == "GET")
            verb = http::verb::get;
        else if (method == "POST")
            verb = http::verb::post;
        else if (method == "DELETE")
            verb = http::verb::delete_;
        else
            verb = http::verb::get;

        http::request<http::string_body> req(verb, path, 11);
        req.set(http::field::host, host);
        req.set(http::field::user_agent, "TransfersMusic/1.0");

        for (const auto &[key, value] : headers)
            req.set(key, value);

        if (!body.empty()) {
            req.body() = body;
            req.prepare_payload();
        }

        http::write(stream, req);

        beast::flat_buffer buf;
        http::response<http::string_body> res;
        http::read(stream, buf, res);

        beast::error_code ec;
        stream.shutdown(ec);

        return {static_cast<int>(res.result_int()), res.body()};

    } catch (const std::exception &e) {
        return {0, e.what()};
    }
}

boost::future<NetworkResponse> NetworkManager::get(const std::string &host,
                                                   const std::string &path,
                                                   const std::map<std::string, std::string> &headers)
{
    return boost::async(boost::launch::async,
                        [=]() { return request(host, path, "GET", "", headers); });
}

boost::future<NetworkResponse> NetworkManager::post(const std::string &host,
                                                    const std::string &path,
                                                    const std::string &body,
                                                    const std::map<std::string, std::string> &headers)
{
    return boost::async(boost::launch::async,
                        [=]() { return request(host, path, "POST", body, headers); });
}

boost::future<NetworkResponse> NetworkManager::del(const std::string &host,
                                                   const std::string &path,
                                                   const std::map<std::string, std::string> &headers)
{
    return boost::async(boost::launch::async,
                        [=]() { return request(host, path, "DELETE", "", headers); });
}
