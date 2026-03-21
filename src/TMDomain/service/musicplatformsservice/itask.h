#ifndef ITASK_H
#define ITASK_H

#include <string>

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

    ITask(Type type);
    Type type() const { return _type; };
    void setToken(const std::string &user_token) { _user_token = user_token; }
    std::string token() { return _user_token; }

private:
    Type _type;
    std::string _user_token;
};

#endif // ITASK_H
