#ifndef MUSICPLATFORMSSERVICE_H
#define MUSICPLATFORMSSERVICE_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include "./service/musicplatformsservice/imusicplotform.h"
#include "appenv.h"

class MusicPlatformsService
{
public:
    explicit MusicPlatformsService(AppEnv *env);

    void addPlatform(boost::shared_ptr<IMusicPlotform> platform);

    boost::future<MusicPlotformResult> runTask(Platform platform,
                                               const boost::shared_ptr<ITask> &task);

    boost::shared_ptr<IMusicPlotform> getPlatform(Platform platform) const;

private:
    AppEnv *_env;
    std::vector<boost::shared_ptr<IMusicPlotform>> _platforms;
};

#endif // MUSICPLATFORMSSERVICE_H
