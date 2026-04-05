#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <map>
#include <string>

#include "boost/thread/future.hpp"

struct NetworkResponse
{
    int status{0};
    std::string body;

    bool isOk() const { return status >= 200 && status < 300; }
};

class NetworkManager
{
public:
    NetworkManager() = delete;

    static boost::future<NetworkResponse> get(const std::string &host,
                                              const std::string &path,
                                              const std::map<std::string, std::string> &headers = {});

    static boost::future<NetworkResponse> post(
        const std::string &host,
        const std::string &path,
        const std::string &body,
        const std::map<std::string, std::string> &headers = {});

    static boost::future<NetworkResponse> del(const std::string &host,
                                              const std::string &path,
                                              const std::map<std::string, std::string> &headers = {});

private:
    static NetworkResponse request(const std::string &host,
                                   const std::string &path,
                                   const std::string &method,
                                   const std::string &body,
                                   const std::map<std::string, std::string> &headers);
};

#endif // NETWORKMANAGER_H
