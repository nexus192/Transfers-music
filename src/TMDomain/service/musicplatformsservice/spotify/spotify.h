#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <map>
#include <string>

#include <boost/thread/future.hpp>

#include "service/musicplatformsservice/imusicplotform.h"
#include "share/networkmanager.h"

class Spotify : public IMusicPlotform
{
public:
    Spotify();

    boost::future<MusicPlotformResult> runTask(const boost::shared_ptr<ITask> &task) override;

    Platform platform() const override { return SpotifyPlatform; }

private:
    MusicPlotformResult authPlatform(const boost::shared_ptr<AuthPlatformTask> &task) override;
    MusicPlotformResult getUser(const boost::shared_ptr<GetUserTask> &task) override;
    MusicPlotformResult getPlayList(const boost::shared_ptr<GetPlayListTask> &task) override;
    MusicPlotformResult getPlayLists(const boost::shared_ptr<GetPlayListsTask> &task) override;
    MusicPlotformResult createPlaylist(const boost::shared_ptr<CreatePlaylistTask> &task) override;
    MusicPlotformResult removePlaylist(const boost::shared_ptr<RemovePlaylistTask> &task) override;
    MusicPlotformResult addMusicToPlaylist(
        const boost::shared_ptr<AddMusicToPlaylistTask> &task) override;

    std::map<std::string, std::string> apiHeaders() const;
    MusicPlotformResult toResult(boost::future<NetworkResponse> future);

    std::string _access_token;
    std::string _user_id;
};

#endif // SPOTIFY_H
