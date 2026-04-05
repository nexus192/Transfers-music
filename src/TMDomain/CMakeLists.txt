cmake_minimum_required(VERSION 3.21)
project(TMDomain LANGUAGES CXX)

set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/lib/boost_1_90_0)
set(Boost_DIR ${BOOST_ROOT}/stage/lib/cmake/Boost-1.90.0)
set(OPENSSL_DIR ${CMAKE_SOURCE_DIR}/lib/openssl)

find_package(Boost 1.90.0 REQUIRED COMPONENTS thread chrono atomic json)

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
    share/networkmanager.h share/networkmanager.cpp
)

target_include_directories(TMDomain PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENSSL_DIR}/include
)

target_compile_definitions(TMDomain PUBLIC
    BOOST_THREAD_PROVIDES_FUTURE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

find_library(OPENSSL_SSL_LIB
    NAMES libssl ssl
    PATHS ${OPENSSL_DIR}/lib/x64
    NO_DEFAULT_PATH
)
find_library(OPENSSL_CRYPTO_LIB
    NAMES libcrypto crypto
    PATHS ${OPENSSL_DIR}/lib/x64
    NO_DEFAULT_PATH
)

target_link_libraries(TMDomain PUBLIC
    Boost::thread
    Boost::chrono
    Boost::atomic
    Boost::json
    ${OPENSSL_SSL_LIB}
    ${OPENSSL_CRYPTO_LIB}
)
