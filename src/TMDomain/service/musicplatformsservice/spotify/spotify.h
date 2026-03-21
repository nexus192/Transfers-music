#ifndef SPOTIFY_H
#define SPOTIFY_H

#include "service/musicplatformsservice/imusicplotform.h"
#include <boost/shared_ptr.hpp>

class Spotify : IMusicPlotform
{
public:
    Spotify();
    MusicPlotformResult runTask(const boost::shared_ptr<ITask> &task) override;

private:
    MusicPlotformResult authPlatform() override;
    MusicPlotformResult getUser() override;
    MusicPlotformResult getPlayList() override;
    MusicPlotformResult getPlayLists() override;
    MusicPlotformResult createPlaylist() override;
    MusicPlotformResult removePlaylist() override;
    MusicPlotformResult addMusicToPlaylist() override;
};

#endif // SPOTIFY_H
