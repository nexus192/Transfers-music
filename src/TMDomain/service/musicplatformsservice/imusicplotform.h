#ifndef IMUSICPLOTFORM_H
#define IMUSICPLOTFORM_H

#include <boost/shared_ptr.hpp>

#include "service/musicplatformsservice/itask.h"

enum Platform {
    Spotify,
};

struct MusicPlotformResult
{
    bool is_error;
};

class IMusicPlotform
{
public:
    IMusicPlotform();
    virtual MusicPlotformResult runTask(const boost::shared_ptr<ITask> &task) = 0;
    virtual bool isConnect() { return is_connect; };

private:
    virtual MusicPlotformResult authPlatform() = 0;
    virtual MusicPlotformResult getUser() = 0;
    virtual MusicPlotformResult getPlayList() = 0;
    virtual MusicPlotformResult getPlayLists() = 0;
    virtual MusicPlotformResult createPlaylist() = 0;
    virtual MusicPlotformResult removePlaylist() = 0;
    virtual MusicPlotformResult addMusicToPlaylist() = 0;

    bool is_connect{false};
};

#endif // IMUSICPLOTFORM_H
