#include "spotify.h"

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/json.hpp>
#include <boost/thread/future.hpp>

#include "share/networkmanager.h"

static std::string base64Encode(const std::string &input)
{
    using namespace boost::archive::iterators;
    using B64 = base64_from_binary<transform_width<const char *, 6, 8>>;
    std::string out(B64(input.data()), B64(input.data() + input.size()));
    while (out.size() % 4)
        out += '=';
    return out;
}

Spotify::Spotify()
    : IMusicPlotform()
{}

boost::future<MusicPlotformResult> Spotify::runTask(const boost::shared_ptr<ITask> &task)
{
    return boost::async(boost::launch::async, [this, task]() -> MusicPlotformResult {
        switch (task->type()) {
        case ITask::AuthPlatform:
            return authPlatform(boost::static_pointer_cast<AuthPlatformTask>(task));
        case ITask::GetUser:
            return getUser(boost::static_pointer_cast<GetUserTask>(task));
        case ITask::GetPlayList:
            return getPlayList(boost::static_pointer_cast<GetPlayListTask>(task));
        case ITask::GetPlayLists:
            return getPlayLists(boost::static_pointer_cast<GetPlayListsTask>(task));
        case ITask::CreatePlaylist:
            return createPlaylist(boost::static_pointer_cast<CreatePlaylistTask>(task));
        case ITask::RemovePlaylist:
            return removePlaylist(boost::static_pointer_cast<RemovePlaylistTask>(task));
        case ITask::AddMusicToPlaylist:
            return addMusicToPlaylist(boost::static_pointer_cast<AddMusicToPlaylistTask>(task));
        }
        return MusicPlotformResult::err("Unknown task type");
    });
}

std::map<std::string, std::string> Spotify::apiHeaders() const
{
    return {
        {"Authorization", "Bearer " + _access_token},
        {"Content-Type", "application/json"},
    };
}

MusicPlotformResult Spotify::toResult(boost::future<NetworkResponse> future)
{
    auto r = future.get();
    if (!r.isOk())
        return MusicPlotformResult::err("HTTP " + std::to_string(r.status) + ": " + r.body);
    return MusicPlotformResult::ok();
}

MusicPlotformResult Spotify::authPlatform(const boost::shared_ptr<AuthPlatformTask> &task)
{
    const std::string creds = task->client_id + ":" + task->client_secret;

    auto r = NetworkManager::post("accounts.spotify.com",
                                  "/api/token",
                                  "grant_type=client_credentials",
                                  {
                                      {"Authorization", "Basic " + base64Encode(creds)},
                                      {"Content-Type", "application/x-www-form-urlencoded"},
                                  })
                 .get();

    if (!r.isOk())
        return MusicPlotformResult::err("Auth failed: " + r.body);

    auto json = boost::json::parse(r.body);
    _access_token = boost::json::value_to<std::string>(json.at("access_token"));
    _is_connected = true;

    return MusicPlotformResult::ok();
}

MusicPlotformResult Spotify::getUser(const boost::shared_ptr<GetUserTask> &)
{
    auto r = NetworkManager::get("api.spotify.com", "/v1/me", apiHeaders()).get();

    if (!r.isOk())
        return MusicPlotformResult::err(r.body);

    auto json = boost::json::parse(r.body);
    _user_id = boost::json::value_to<std::string>(json.at("id"));

    return MusicPlotformResult::ok();
}

MusicPlotformResult Spotify::getPlayList(const boost::shared_ptr<GetPlayListTask> &task)
{
    return toResult(
        NetworkManager::get("api.spotify.com", "/v1/playlists/" + task->playlist_id, apiHeaders()));
}

MusicPlotformResult Spotify::getPlayLists(const boost::shared_ptr<GetPlayListsTask> &)
{
    return toResult(NetworkManager::get("api.spotify.com", "/v1/me/playlists", apiHeaders()));
}

MusicPlotformResult Spotify::createPlaylist(const boost::shared_ptr<CreatePlaylistTask> &task)
{
    if (_user_id.empty())
        return MusicPlotformResult::err("Call GetUser before CreatePlaylist");

    boost::json::object body;
    body["name"] = task->name;
    body["description"] = task->description;
    body["public"] = task->is_public;

    return toResult(NetworkManager::post("api.spotify.com",
                                         "/v1/users/" + _user_id + "/playlists",
                                         boost::json::serialize(body),
                                         apiHeaders()));
}

MusicPlotformResult Spotify::removePlaylist(const boost::shared_ptr<RemovePlaylistTask> &task)
{
    return toResult(NetworkManager::del("api.spotify.com",
                                        "/v1/playlists/" + task->playlist_id + "/followers",
                                        apiHeaders()));
}

MusicPlotformResult Spotify::addMusicToPlaylist(const boost::shared_ptr<AddMusicToPlaylistTask> &task)
{
    boost::json::array uris;
    for (const auto &uri : task->track_uris) {
        uris.push_back(boost::json::value(uri));
    }

    boost::json::object body;
    body["uris"] = uris;

    return toResult(NetworkManager::post("api.spotify.com",
                                         "/v1/playlists/" + task->playlist_id + "/tracks",
                                         boost::json::serialize(body),
                                         apiHeaders()));
}
