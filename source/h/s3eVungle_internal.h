/*
 * Internal header for the s3eVungle extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EVUNGLE_INTERNAL_H
#define S3EVUNGLE_INTERNAL_H

#include "s3eTypes.h"
#include "s3eVungle.h"
#include "s3eVungle_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eVungleInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eVungleInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eVungleTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eVungleTerminate_platform();
void s3eVungleDefaultUserData_platform(s3eVungleUserData* out_userData);

s3eResult s3eVungleRegister_platform(s3eVungleCallback callbackID, s3eCallback callbackFn, void* userData);

s3eResult s3eVungleUnRegister_platform(s3eVungleCallback callbackID, s3eCallback callbackFn);

void s3eVungleStart_platform(const char* pubAppID);

void s3eVungleStartWithUserData_platform(const char* pubAppID, const s3eVungleUserData* userData);

s3eResult s3eVungleGetCurrentStatusData_platform(s3eVungleStatusData* out_statusData);

s3eBool s3eVungleIsRunning_platform();

void s3eVunglePrintCacheFiles_platform();

void s3eVunglePrintDeviceSettings_platform();

const char* s3eVungleGetVersionString_platform();

s3eBool s3eVungleIsAdAvailable_platform();

void s3eVunglePlayModalAd_platform(s3eBool animate, s3eBool showClose);

void s3eVunglePlayIncentivizedAd_platform(s3eBool animate, s3eBool showClose, const char* userTag);

int32 s3eVungleGetCacheSize_platform();

void s3eVungleSetCacheSize_platform(int32 megabytes);

void s3eVungleSetLogToStdout_platform(s3eBool state);

void s3eVungleSetSoundEnabled_platform(s3eBool enabled);

void s3eVungleSetMuteIfMusicIsPlaying_platform(s3eBool state);

void s3eVungleSetCustomCountDownText_platform(const char* text);

void s3eVungleSetAlertBoxSettings_platform(const char* title, const char* body, const char* leftButtonTitle, const char* rightButtonTitle);

void s3eVungleSetAllowAutoRotate_platform(s3eBool allow);


#endif /* !S3EVUNGLE_INTERNAL_H */