//
// Created by prith on 12/21/2016.
//

#ifndef ANDROIDREMOTECONTROL_VIDEOMANAGER_H
#define ANDROIDREMOTECONTROL_VIDEOMANAGER_H


#include <string>
#include <unordered_map>
#include <vector>
#include "enums.h"
#include "Saveable.h"

class VideoPlayer : public Saveable
{

public:

    static VideoPlayer& getInstance();

    bool PlayVideo(VIDEO_TYPE videoId);
    bool StopVideo(VIDEO_TYPE videoId);
    void StopCurrentlyPlayingVideo();
    void Init();
    void SetVideoName(VIDEO_TYPE vidId, const std::string &name);
    void SetVideoDelay(VIDEO_TYPE vidId, int delay);
    void SetCommandName(COMMAND_TYPE cmdId, const std::string &name);

    const std::string& GetVideoName(VIDEO_TYPE vidId) const;
    int GetVideoDelay(VIDEO_TYPE vidId) const;
    const std::string& GetCommandName(COMMAND_TYPE cmdId) const;

    virtual void Save(std::ofstream* saveFile) override;

private:
    VideoPlayer();
    std::string mVideoNames[VIDEO_TYPE_MAX];
    int mVideoDelay[VIDEO_TYPE_MAX];
    std::string mCommandNames[COMMAND_TYPE_MAX];

    VIDEO_TYPE mCurrentlyPlaying;

    static const std::string mVideoKey;
    static const std::string mVideoDelayKey;
    static const std::string mCommandKey;
};


#endif //ANDROIDREMOTECONTROL_VIDEOMANAGER_H
