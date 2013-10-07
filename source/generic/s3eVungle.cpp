/*
Generic implementation of the s3eVungle extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eVungle_internal.h"

#include "s3eEdk.h"

s3eResult s3eVungleInit()
{
    //Add any generic initialisation code here
    return s3eVungleInit_platform();
}

void s3eVungleTerminate()
{
    //Add any generic termination code here
    s3eVungleTerminate_platform();
}

void s3eVungleDefaultUserData(s3eVungleUserData* out_userData)
{
	s3eVungleDefaultUserData_platform(out_userData);
}

s3eResult s3eVungleRegister(s3eVungleCallback callbackID, s3eCallback callbackFn, void* userData)
{
    return s3eEdkCallbacksRegister(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_MAX, callbackID, callbackFn, userData, false);
}

s3eResult s3eVungleUnRegister(s3eVungleCallback callbackID, s3eCallback callbackFn)
{
    return s3eEdkCallbacksUnRegister(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_MAX, callbackID, callbackFn);
}

void s3eVungleStart(const char* pubAppID)
{
	s3eVungleStart_platform(pubAppID);
}

void s3eVungleStartWithUserData(const char* pubAppID, const s3eVungleUserData* userData)
{
	s3eVungleStartWithUserData_platform(pubAppID, userData);
}

void s3eVungleGetCurrentStatusData(s3eVungleStatusData* out_statusData)
{
	s3eVungleGetCurrentStatusData_platform(out_statusData);
}

s3eBool s3eVungleIsRunning()
{
	return s3eVungleIsRunning_platform();
}

void s3eVunglePrintCacheFiles()
{
	s3eVunglePrintCacheFiles_platform();
}

void s3eVunglePrintDeviceSettings()
{
	s3eVunglePrintDeviceSettings_platform();
}

const char* s3eVungleGetVersionString()
{
	return s3eVungleGetVersionString_platform();
}

s3eBool s3eVungleIsAdAvailable()
{
	return s3eVungleIsAdAvailable_platform();
}

void s3eVunglePlayModalAd(s3eBool animate, s3eBool showClose)
{
	s3eVunglePlayModalAd_platform(animate, showClose);
}

void s3eVunglePlayIncentivizedAd(s3eBool animate, s3eBool showClose, const char* userTag)
{
	s3eVunglePlayIncentivizedAd_platform(animate, showClose, userTag);
}

int32 s3eVungleGetCacheSize()
{
	return s3eVungleGetCacheSize_platform();
}

void s3eVungleSetCacheSize(int32 megabytes)
{
	s3eVungleSetCacheSize_platform(megabytes);
}

void s3eVungleSetLogToStdout(s3eBool state)
{
	s3eVungleSetLogToStdout_platform(state);
}

void s3eVungleSetSoundEnabled(s3eBool enabled)
{
	s3eVungleSetSoundEnabled_platform(enabled);
}

void s3eVungleSetMuteIfMusicIsPlaying(s3eBool state)
{
	s3eVungleSetMuteIfMusicIsPlaying_platform(state);
}

s3eBool s3eVungleSetCustomCountDownText(const char* text)
{
	return s3eVungleSetCustomCountDownText_platform(text);
}

void s3eVungleSetAlertBoxSettings(const char* title, const char* body, const char* leftButtonTitle, const char* rightButtonTitle)
{
	s3eVungleSetAlertBoxSettings_platform(title, body, leftButtonTitle, rightButtonTitle);
}

void s3eVungleSetAllowAutoRotate(s3eBool allow)
{
	s3eVungleSetAllowAutoRotate_platform(allow);
}
