//
// Created by prith on 12/21/2016.
//

#include "VideoPlayer.h"
#include "NetworkController.h"
#include "helper.h"

const std::string VideoPlayer::mVideoKey = "video";
const std::string VideoPlayer::mCommandKey = "command";

VideoPlayer& VideoPlayer::getInstance()
{
    static VideoPlayer player;

    return player;
}

void VideoPlayer::PlayVideo(VIDEO_TYPE videoId)
{
    if (videoId > VIDEO_TYPE_INVALID && videoId < VIDEO_TYPE_MAX)
    {
        const std::string message = mCommandNames[COMMAND_TYPE_START] + " " + mVideoNames[videoId];
        NetworkController::getInstance().SendUDPMessage(message);
        mCurrentlyPlaying = videoId;
    }
}

void VideoPlayer::StopVideo(VIDEO_TYPE videoId)
{
    if (videoId > VIDEO_TYPE_INVALID && videoId < VIDEO_TYPE_MAX)
    {
        const std::string message = mCommandNames[COMMAND_TYPE_STOP] + " " + mVideoNames[videoId];
        NetworkController::getInstance().SendUDPMessage(message);

        mCurrentlyPlaying = VIDEO_TYPE_INVALID;
    }
}

void VideoPlayer::SetVideoName(VIDEO_TYPE vidId, std::string& name)
{
    mVideoNames[vidId] = name;
}
void VideoPlayer::SetCommandName(COMMAND_TYPE cmdId, std::string& name)
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
}

void VideoPlayer::Init()
{
    PersistentDataManager& dataManager = PersistentDataManager::getInstance();
    std::string key;

    for(int i = VIDEO_TYPE_INVALID + 1 ; i < VIDEO_TYPE_MAX ; ++i)
    {
        key = mVideoKey + Helper::to_string(i);
        mVideoNames[i] = dataManager.GetData(key);
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
            line = mVideoKey + Helper::to_string(i) + "=" + mVideoNames[i] + "\n";
            (*saveFile) << line;
        }

        for(int i = COMMAND_TYPE_INVALID + 1 ; i < COMMAND_TYPE_MAX ; ++i)
        {
            line = mCommandKey + Helper::to_string(i) + "=" + mCommandNames[i] + "\n";
            (*saveFile) << line;
        }
    }
}
