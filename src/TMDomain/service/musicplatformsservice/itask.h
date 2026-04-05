#ifndef ITASK_H
#define ITASK_H

#include <string>
#include <vector>

class ITask
{
public:
    enum Type {
        AuthPlatform,
        GetUser,
        GetPlayList,
        GetPlayLists,
        CreatePlaylist,
        RemovePlaylist,
        AddMusicToPlaylist,
    };

    explicit ITask(Type type)
        : _type(type)
    {}
    virtual ~ITask() = default;

    Type type() const { return _type; }
    void setToken(const std::string &token) { _user_token = token; }
    std::string token() const { return _user_token; }

private:
    Type _type;
    std::string _user_token;
};

// ─────────────────────────────────────────────────────────
// Конкретные задачи — каждая несёт свои входные данные
// ─────────────────────────────────────────────────────────

class AuthPlatformTask : public ITask
{
public:
    AuthPlatformTask(const std::string &client_id, const std::string &client_secret)
        : ITask(ITask::AuthPlatform)
        , client_id(client_id)
        , client_secret(client_secret)
    {}

    std::string client_id;
    std::string client_secret;
};

class GetUserTask : public ITask
{
public:
    GetUserTask()
        : ITask(ITask::GetUser)
    {}
};

class GetPlayListTask : public ITask
{
public:
    explicit GetPlayListTask(const std::string &playlist_id)
        : ITask(ITask::GetPlayList)
        , playlist_id(playlist_id)
    {}

    std::string playlist_id;
};

class GetPlayListsTask : public ITask
{
public:
    GetPlayListsTask()
        : ITask(ITask::GetPlayLists)
    {}
};

class CreatePlaylistTask : public ITask
{
public:
    CreatePlaylistTask(const std::string &name,
                       const std::string &description = "",
                       bool is_public = false)
        : ITask(ITask::CreatePlaylist)
        , name(name)
        , description(description)
        , is_public(is_public)
    {}

    std::string name;
    std::string description;
    bool is_public;
};

class RemovePlaylistTask : public ITask
{
public:
    explicit RemovePlaylistTask(const std::string &playlist_id)
        : ITask(ITask::RemovePlaylist)
        , playlist_id(playlist_id)
    {}

    std::string playlist_id;
};

class AddMusicToPlaylistTask : public ITask
{
public:
    AddMusicToPlaylistTask(const std::string &playlist_id,
                           const std::vector<std::string> &track_uris)
        : ITask(ITask::AddMusicToPlaylist)
        , playlist_id(playlist_id)
        , track_uris(track_uris)
    {}

    std::string playlist_id;
    std::vector<std::string> track_uris; // "spotify:track:XXXXX"
};

#endif // ITASK_H
