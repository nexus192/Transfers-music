#ifndef MUSIC_H
#define MUSIC_H

#include <string>

#include "artist.h"

class Music
{
public:
    Music();

    std::string id;
    std::string name;
    int duration_ms;
    Artist artist;
};

#endif // MUSIC_H
