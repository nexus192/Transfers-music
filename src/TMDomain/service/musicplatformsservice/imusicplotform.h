#ifndef IMUSICPLOTFORM_H
#define IMUSICPLOTFORM_H

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/thread/future.hpp>

#include "itask.h"

enum Platform {
    SpotifyPlatform,
};

struct MusicPlotformResult
{
    bool is_error{false};
    std::string error_message;

    static MusicPlotformResult ok() { return {false, ""}; }
    static MusicPlotformResult err(const std::string &msg) { return {true, msg}; }
};

class IMusicPlotform
{
public:
    IMusicPlotform() = default;
    virtual ~IMusicPlotform() = default;

    virtual boost::future<MusicPlotformResult> runTask(const boost::shared_ptr<ITask> &task) = 0;

    virtual bool isConnected() const { return _is_connected; }
    virtual Platform platform() const = 0;

protected:
    bool _is_connected{false};

private:
    virtual MusicPlotformResult authPlatform(const boost::shared_ptr<AuthPlatformTask> &task) = 0;
    virtual MusicPlotformResult getUser(const boost::shared_ptr<GetUserTask> &task) = 0;
    virtual MusicPlotformResult getPlayList(const boost::shared_ptr<GetPlayListTask> &task) = 0;
    virtual MusicPlotformResult getPlayLists(const boost::shared_ptr<GetPlayListsTask> &task) = 0;
    virtual MusicPlotformResult createPlaylist(const boost::shared_ptr<CreatePlaylistTask> &task) = 0;
    virtual MusicPlotformResult removePlaylist(const boost::shared_ptr<RemovePlaylistTask> &task) = 0;
    virtual MusicPlotformResult addMusicToPlaylist(
        const boost::shared_ptr<AddMusicToPlaylistTask> &task)
        = 0;
};

#endif // IMUSICPLOTFORM_H
