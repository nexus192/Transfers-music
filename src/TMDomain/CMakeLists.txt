cmake_minimum_required(VERSION 3.21)

project(TMDomain LANGUAGES CXX)

set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/lib/boost_1_90_0)

find_package(Boost REQUIRED)

add_library(TMDomain STATIC
    appenv.h appenv.cpp
    model/playlists.h
    entities/user.h entities/user.cpp
    entities/music.h entities/music.cpp
    entities/artist.h entities/artist.cpp
    entities/playlist.h entities/playlist.cpp
    service/musicplatformsservice/musicplatformsservice.h service/musicplatformsservice/musicplatformsservice.cpp
    service/musicplatformsservice/imusicplotform.h service/musicplatformsservice/imusicplotform.cpp
    service/musicplatformsservice/spotify/spotify.h service/musicplatformsservice/spotify/spotify.cpp
    service/iofiles/iofiles.h service/iofiles/iofiles.cpp
    service/musicplatformsservice/itask.h service/musicplatformsservice/itask.cpp
)

target_include_directories(TMDomain PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(TMDomain PRIVATE ${BOOST_ROOT})
