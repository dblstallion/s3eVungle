/*
 * iphone-specific implementation of the s3eVungle extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eVungle_internal.h"

s3eResult s3eVungleInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eVungleTerminate_platform()
{
    // Add any platform-specific termination code here
}

void s3eVungleDefaultUserData_platform(s3eVungleUserData* out_userData)
{
}

s3eResult s3eVungleRegister_platform(s3eVungleCallback callbackID, s3eCallback callbackFn, void* userData)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eVungleUnRegister_platform(s3eVungleCallback callbackID, s3eCallback callbackFn)
{
    return S3E_RESULT_ERROR;
}

void s3eVungleStart_platform(const char* pubAppID)
{
}

void s3eVungleStartWithUserData_platform(const char* pubAppID, const s3eVungleUserData* userData)
{
}

s3eResult s3eVungleGetCurrentStatusData_platform(s3eVungleStatusData* out_statusData)
{
    return S3E_RESULT_ERROR;
}

s3eBool s3eVungleIsRunning_platform()
{
    return S3E_FALSE;
}

void s3eVunglePrintCacheFiles_platform()
{
}

void s3eVunglePrintDeviceSettings_platform()
{
}

const char* s3eVungleGetVersionString_platform()
{
    return NULL;
}

s3eBool s3eVungleIsAdAvailable_platform()
{
    return S3E_FALSE;
}

void s3eVunglePlayModalAd_platform(s3eBool animate, s3eBool showClose)
{
}

void s3eVunglePlayIncentivizedAd_platform(s3eBool animate, s3eBool showClose, const char* userTag)
{
}

int32 s3eVungleGetCacheSize_platform()
{
    return 0;
}

void s3eVungleSetCacheSize_platform(int32 megabytes)
{
}

void s3eVungleSetLogToStdout_platform(s3eBool state)
{
}

void s3eVungleSetSoundEnabled_platform(s3eBool enabled)
{
}

void s3eVungleSetMuteIfMusicIsPlaying_platform(s3eBool state)
{
}

void s3eVungleSetCustomCountDownText_platform(const char* text)
{
}

void s3eVungleSetAlertBoxSettings_platform(const char* title, const char* body, const char* leftButtonTitle, const char* rightButtonTitle)
{
}

void s3eVungleSetAllowAutoRotate_platform(s3eBool allow)
{
}
