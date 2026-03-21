#include "spotify.h"

Spotify::Spotify()
    : IMusicPlotform{}
{}

MusicPlotformResult Spotify::runTask(const boost::shared_ptr<ITask> &task)
{
    if (task->type() == ITask::Type::AuthPlatform) {
        return authPlatform();
    } else if (task->type() == ITask::Type::GetUser) {
        return getUser();
    } else if (task->type() == ITask::Type::GetPlayList) {
        return getPlayList();
    } else if (task->type() == ITask::Type::GetPlayLists) {
        return getPlayLists();
    } else if (task->type() == ITask::Type::CreatePlaylist) {
        return createPlaylist();
    } else if (task->type() == ITask::Type::RemovePlaylist) {
        return removePlaylist();
    } else if (task->type() == ITask::Type::AddMusicToPlaylist) {
        return addMusicToPlaylist();
    }

    return MusicPlotformResult{};
}

MusicPlotformResult Spotify::authPlatform()
{
    return MusicPlotformResult{};
}

MusicPlotformResult Spotify::getUser()
{
    return MusicPlotformResult{};
}

MusicPlotformResult Spotify::getPlayList()
{
    return MusicPlotformResult{};
}

MusicPlotformResult Spotify::getPlayLists()
{
    return MusicPlotformResult{};
}

MusicPlotformResult Spotify::createPlaylist()
{
    return MusicPlotformResult{};
}

MusicPlotformResult Spotify::removePlaylist()
{
    return MusicPlotformResult{};
}

MusicPlotformResult Spotify::addMusicToPlaylist()
{
    return MusicPlotformResult{};
}
