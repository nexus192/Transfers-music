#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>

class Playlist
{
public:
    Playlist();

    std::string id;
    std::string name;
    std::vector<std::string> images;
    int total_items{0};
};

#endif // PLAYLIST_H
