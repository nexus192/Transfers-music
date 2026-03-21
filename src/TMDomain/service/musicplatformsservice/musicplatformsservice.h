#ifndef MUSICPLATFORMSSERVICE_H
#define MUSICPLATFORMSSERVICE_H

#include <vector>

#include "appenv.h"
#include "service/musicplatformsservice/imusicplotform.h"

class MusicPlatformsService
{
public:
    MusicPlatformsService(AppEnv *env);
    void runTask();

private:
    AppEnv *env;
    std::vector<IMusicPlotform> platforms;
};

#endif // MUSICPLATFORMSSERVICE_H
