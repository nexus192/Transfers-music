#include "musicplatformsservice.h"

MusicPlatformsService::MusicPlatformsService(AppEnv *env)
    : _env(env)
{}

void MusicPlatformsService::addPlatform(boost::shared_ptr<IMusicPlotform> platform)
{
    _platforms.push_back(std::move(platform));
}

boost::future<MusicPlotformResult> MusicPlatformsService::runTask(
    Platform platform, const boost::shared_ptr<ITask> &task)
{
    auto p = getPlatform(platform);
    if (!p) {
        boost::promise<MusicPlotformResult> promise;
        promise.set_value(MusicPlotformResult::err("Platform not registered"));
        return promise.get_future();
    }
    return p->runTask(task);
}

boost::shared_ptr<IMusicPlotform> MusicPlatformsService::getPlatform(Platform platform) const
{
    for (const auto &p : _platforms)
        if (p->platform() == platform)
            return p;
    return nullptr;
}
