/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
#ifndef S3E_EXT_VUNGLE_H
#define S3E_EXT_VUNGLE_H

#include "s3eTypes.h"

typedef double s3eVungleTimeInterval;

typedef enum s3eVungleCallback
{
	/**
	 * Called when a video ad has finished playing
	 * May be called more than once per ad if the user decides to re-watch the video
	 * systemData will be a pointer to an s3eVunglePlayData instance
	 */
	s3eVungleCallback_MoviePlayed,
	/**
	 * Called when the Vungle status is changed
	 * systemData will be a pointer to an s3eVungleStatusData instance
	 */
	s3eVungleCallback_StatusUpdate,
	/**
	 * Called when the Vungle UIViewController is hidden
	 * systemData will be NULL
	 */
	s3eVungleCallback_ViewDidDisappear,
	/**
	 * Called when the Vungle UIViewController will be shown
	 * systemData will be NULL
	 */
	s3eVungleCallback_ViewWillAppear,
	/**
	 * Called when the Vungle AppStoreViewDidDisappear delegate is called
	 * systemData will be NULL
	 */
	s3eVungleCallback_AppStoreViewDidDisappear,
	/**
	 * Called when the Vungle API wants to log some test
	 * systemData will be a const char* containing the logging text
	 */
	s3eVungleCallback_Logging,
	
	// Marker for the last callback
	s3eVungleCallback_MAX
} s3eVungleCallback;

typedef enum s3eVungleAdOrientation
{
    s3eVungleAdOrientationUnknown,
    s3eVungleAdOrientationPortrait,
    s3eVungleAdOrientationLandscape,
    
    s3eVungleAdOrientationFirst   = s3eVungleAdOrientationPortrait,
    s3eVungleAdOrientationLast    = s3eVungleAdOrientationLandscape,
    s3eVungleAdOrientationDefault = s3eVungleAdOrientationPortrait
} s3eVungleAdOrientation;

typedef enum s3eVungleGender
{
    s3eVungleGenderUnknown,
    s3eVungleGenderMale,
    s3eVungleGenderFemale
} s3eVungleGender;

typedef enum s3eVungleAdType
{
    s3eVungleAdTypeUnknown,
    
    s3eVungleAdTypeReal,
    
    s3eVungleAdTypeFakePreBundleHTML,
    s3eVungleAdTypeFakePreBundleZip,
    s3eVungleAdTypeFakePostBundleHTML,
    s3eVungleAdTypeFakePostBundleZip,
    s3eVungleAdTypeFakeMovie,
    
    s3eVungleAdTypeFakeFirst = s3eVungleAdTypeFakePreBundleHTML,
    s3eVungleAdTypeFakeLast  = s3eVungleAdTypeFakeMovie
} s3eVungleAdType;

typedef enum s3eVungleStatus
{
    s3eVungleStatusOkay,
    s3eVungleStatusNetworkError,
    s3eVungleStatusDiskError
} s3eVungleStatus;

typedef struct s3eVungleUserData
{
	int32 age;
    s3eVungleGender gender;
    s3eVungleAdOrientation adOrientation;
    s3eBool locationEnabled;   // allow vungle to get user location
} s3eVungleUserData;

typedef struct s3eVunglePlayData
{
    s3eVungleTimeInterval start;        // time when we started playing
    s3eVungleTimeInterval movieTotal;   // total length of the movie
    s3eVungleTimeInterval movieViewed;  // total length viewed by the user
	s3eBool playedFull;
} s3eVunglePlayData;

typedef struct s3eVungleStatusData
{
    int32 videoAdsCached;
    int32 videoAdsUnviewed;
    s3eVungleStatus status;
} s3eVungleStatusData;
// \cond HIDDEN_DEFINES
S3E_BEGIN_C_DECL
// \endcond

/**
 * Returns S3E_TRUE if the Vungle extension is available.
 */
s3eBool s3eVungleAvailable();

void s3eVungleDefaultUserData(s3eVungleUserData* out_userData);

s3eResult s3eVungleRegister(s3eVungleCallback callbackID, s3eCallback callbackFn, void* userData);

s3eResult s3eVungleUnRegister(s3eVungleCallback callbackID, s3eCallback callbackFn);

void s3eVungleStart(const char* pubAppID);

void s3eVungleStartWithUserData(const char* pubAppID, const s3eVungleUserData* userData);

void s3eVungleGetCurrentStatusData(s3eVungleStatusData* out_statusData);

s3eBool s3eVungleIsRunning();

void s3eVunglePrintCacheFiles();

void s3eVunglePrintDeviceSettings();

const char* s3eVungleGetVersionString();

s3eBool s3eVungleIsAdAvailable();

void s3eVunglePlayModalAd(s3eBool animate, s3eBool showClose);

void s3eVunglePlayIncentivizedAd(s3eBool animate, s3eBool showClose, const char* userTag);

int32 s3eVungleGetCacheSize();

void s3eVungleSetCacheSize(int32 megabytes);

void s3eVungleSetLogToStdout(s3eBool state);

void s3eVungleSetSoundEnabled(s3eBool enabled);

void s3eVungleSetMuteIfMusicIsPlaying(s3eBool state);

s3eBool s3eVungleSetCustomCountDownText(const char* text);

void s3eVungleSetAlertBoxSettings(const char* title, const char* body, const char* leftButtonTitle, const char* rightButtonTitle);

void s3eVungleSetAllowAutoRotate(s3eBool allow);

S3E_END_C_DECL

#endif /* !S3E_EXT_VUNGLE_H */