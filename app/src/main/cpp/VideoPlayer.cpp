//
// Created by prith on 12/21/2016.
//

#include "VideoPlayer.h"
#include "NetworkController.h"
#include "helper.h"

const std::string VideoPlayer::mVideoKey = "video";
const std::string VideoPlayer::mVideoDelayKey = "videodelay";
const std::string VideoPlayer::mCommandKey = "command";

VideoPlayer& VideoPlayer::getInstance()
{
    static VideoPlayer player;

    return player;
}

bool VideoPlayer::PlayVideo(VIDEO_TYPE videoId)
{
    bool videoPlayed = false;
    if (videoId > VIDEO_TYPE_INVALID && videoId < VIDEO_TYPE_MAX)
    {
        const std::string message = mCommandNames[COMMAND_TYPE_START] + " " + mVideoNames[videoId] + "\n";
        videoPlayed = NetworkController::getInstance().SendMessage(message);
        mCurrentlyPlaying = videoId;
    }
    return videoPlayed;
}

bool VideoPlayer::StopVideo(VIDEO_TYPE videoId)
{
    bool videoStopped = false;
    if (videoId > VIDEO_TYPE_INVALID && videoId < VIDEO_TYPE_MAX && mCurrentlyPlaying == videoId)
    {
        const std::string message = mCommandNames[COMMAND_TYPE_STOP] + " " + mVideoNames[videoId] + "\n";
        videoStopped = NetworkController::getInstance().SendMessage(message);

        mCurrentlyPlaying = VIDEO_TYPE_INVALID;
    }

    return videoStopped;
}

void VideoPlayer::SetVideoName(VIDEO_TYPE vidId, const std::string &name)
{
    mVideoNames[vidId] = name;
}
void VideoPlayer::SetCommandName(COMMAND_TYPE cmdId, const std::string &name)
{
    mCommandNames[cmdId] = name;
}

void VideoPlayer::StopCurrentlyPlayingVideo()
{
    StopVideo(mCurrentlyPlaying);
}

const std::string& VideoPlayer::GetVideoName(VIDEO_TYPE vidId) const
{
    return mVideoNames[vidId];
}

const std::string& VideoPlayer::GetCommandName(COMMAND_TYPE cmdId) const
{
    return mCommandNames[cmdId];
}

VideoPlayer::VideoPlayer() :mCurrentlyPlaying(VIDEO_TYPE_INVALID)
{
    memset(mVideoDelay, 0 , sizeof(int) * VIDEO_TYPE_MAX);
}

void VideoPlayer::Init()
{
    PersistentDataManager& dataManager = PersistentDataManager::getInstance();
    std::string key;

    for(int i = VIDEO_TYPE_INVALID + 1 ; i < VIDEO_TYPE_MAX ; ++i)
    {
        std::string temp = Helper::to_string(i);
        key = mVideoKey + temp;
        mVideoNames[i] = dataManager.GetData(key);

        key = mVideoDelayKey + temp;
        temp = dataManager.GetData(key);
        mVideoDelay[i] = Helper::to_int(temp);
    }

    for(int i = COMMAND_TYPE_INVALID + 1 ; i < COMMAND_TYPE_MAX ; ++i)
    {
        key = mCommandKey + Helper::to_string(i);
        mCommandNames[i] = dataManager.GetData(key);
    }
}

void VideoPlayer::Save(std::ofstream *saveFile)
{
    if(saveFile)
    {
        std::string line;
        for(int i = VIDEO_TYPE_INVALID + 1 ; i < VIDEO_TYPE_MAX ; ++i)
        {
            const std::string indexString = Helper::to_string(i);
            line = mVideoKey + indexString + "=" + mVideoNames[i] + "\n";

            line += mVideoDelayKey + indexString + "=" + Helper::to_string(mVideoDelay[i]) + "\n";

            (*saveFile) << line;
        }

        for(int i = COMMAND_TYPE_INVALID + 1 ; i < COMMAND_TYPE_MAX ; ++i)
        {
            line = mCommandKey + Helper::to_string(i) + "=" + mCommandNames[i] + "\n";
            (*saveFile) << line;
        }
    }
}

int VideoPlayer::GetVideoDelay(VIDEO_TYPE vidId) const {
    return mVideoDelay[vidId];
}

void VideoPlayer::SetVideoDelay(VIDEO_TYPE vidId, int delay) {
    mVideoDelay[vidId] = delay;
}






