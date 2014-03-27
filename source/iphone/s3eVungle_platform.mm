/*
 * iphone-specific implementation of the s3eVungle extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eVungle_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_iphone.h"

#import <UIKit/UIKit.h>
#import "vunglepub.h"

@interface S3EVunglePubDelegate : NSObject <VGVunglePubDelegate>
@end

@implementation S3EVunglePubDelegate
-(void)vungleMoviePlayed:(VGPlayData*)playData
{
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_MoviePlayed))
	{
		s3eVunglePlayData pd;
        pd.start = playData.start;
        pd.movieTotal = playData.movieTotal;
        pd.movieViewed = playData.movieViewed;
        pd.playedFull = [playData playedFull];
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_MoviePlayed, &pd, sizeof(pd));
	}
}

-(void)vungleStatusUpdate:(VGStatusData*)statusData
{
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_StatusUpdate))
	{
		s3eVungleStatusData sd;
        sd.videoAdsCached = statusData.videoAdsCached;
        sd.videoAdsUnviewed = statusData.videoAdsUnviewed;
        sd.status = (s3eVungleStatus)statusData.status;
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_StatusUpdate, &sd, sizeof(sd));
	}
}

-(void)vungleViewDidDisappear:(UIViewController*)viewController
{
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_ViewDidDisappear))
	{
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_ViewDidDisappear);
	}
}

-(void)vungleViewWillAppear:(UIViewController*)viewController
{
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_ViewWillAppear))
	{
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_ViewWillAppear);
	}
}

-(void)vungleAppStoreViewDidDisappear
{
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_AppStoreViewDidDisappear))
	{
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_AppStoreViewDidDisappear);
	}
}

-(void)vungleAppStoreWillAppear
{
    if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_AppStoreWillAppear))
	{
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_AppStoreWillAppear);
	}
}
@end

// the Vungle Delegate singleton
static S3EVunglePubDelegate *gDelegate = NULL;

s3eResult s3eVungleInit_platform()
{
    if (!gDelegate)
    {
        gDelegate = [[S3EVunglePubDelegate alloc] init];
    }

    [VGVunglePub setDelegate:gDelegate];

    return S3E_RESULT_SUCCESS;
}

void s3eVungleTerminate_platform()
{
    [VGVunglePub stop];

    if (gDelegate)
    {
        [gDelegate release];
        gDelegate = NULL;
    }
}

void s3eVungleDefaultUserData_platform(s3eVungleUserData* out_userData)
{
    VGUserData* data = [VGUserData defaultUserData];

    out_userData->age = data.age;
    out_userData->gender = (s3eVungleGender)data.gender;
    out_userData->adOrientation = (s3eVungleAdOrientation)data.adOrientation;
    out_userData->locationEnabled = data.locationEnabled;
}

void s3eVungleStart_platform(const char* pubAppID)
{
    NSString *nsAppId = [[NSString alloc] initWithUTF8String:pubAppID];
	[VGVunglePub startWithPubAppID:nsAppId];
    [nsAppId release];
}

void s3eVungleStartWithUserData_platform(const char* pubAppID, const s3eVungleUserData* userData)
{
    VGUserData* data = [VGUserData defaultUserData];

    data.age = userData->age;
    data.gender = (VGGender)userData->gender;
    data.adOrientation = (VGAdOrientation)userData->adOrientation;
    data.locationEnabled = userData->locationEnabled;

    NSString *nsAppId = [[NSString alloc] initWithUTF8String:pubAppID];
    [VGVunglePub startWithPubAppID:nsAppId userData:data];
    [nsAppId release];
}

void s3eVungleGetCurrentStatusData_platform(s3eVungleStatusData* out_statusData)
{
    VGStatusData *data = [VGVunglePub currentStatusData];

    out_statusData->videoAdsCached = data.videoAdsCached;
    out_statusData->videoAdsUnviewed = data.videoAdsUnviewed;
    out_statusData->status = (s3eVungleStatus)data.status;
}

s3eBool s3eVungleIsRunning_platform()
{
    return [VGVunglePub running];
}

void s3eVunglePrintCacheFiles_platform()
{
	[VGVunglePub showCacheFiles];
}

void s3eVunglePrintDeviceSettings_platform()
{
	[VGVunglePub showDeviceSettings];
}

const char* s3eVungleGetVersionString_platform()
{
    return [[VGVunglePub versionString] UTF8String];
}

s3eBool s3eVungleIsAdAvailable_platform()
{
    return [VGVunglePub adIsAvailable];
}

void s3eVunglePlayModalAd_platform(s3eBool animate, s3eBool showClose)
{
    UIViewController* viewController = s3eEdkGetUIViewController();
    [VGVunglePub playModalAd:viewController animated:animate showClose:showClose];
}

void s3eVunglePlayIncentivizedAd_platform(s3eBool animate, s3eBool showClose, const char* userTag)
{
    UIViewController* viewController = s3eEdkGetUIViewController();
    NSString *nsUserTag = userTag ? [[NSString alloc] initWithUTF8String:userTag] : NULL;

    [VGVunglePub playIncentivizedAd:viewController animated:animate showClose:showClose userTag:nsUserTag];

    if(nsUserTag)
        [nsUserTag release];
}

int32 s3eVungleGetCacheSize_platform()
{
    return [VGVunglePub cacheSizeGet];
}

void s3eVungleSetCacheSize_platform(int32 megabytes)
{
    [VGVunglePub cacheSizeSet:megabytes];
}

void s3eVungleSetLogToStdout_platform(s3eBool state)
{
    [VGVunglePub logToStdout:state];
}

void s3eVungleSetSoundEnabled_platform(s3eBool enabled)
{
    [VGVunglePub setSoundEnabled:enabled];
}

void s3eVungleSetMuteIfMusicIsPlaying_platform(s3eBool state)
{
    [VGVunglePub muteIfMusicPlaying:state];
}

s3eBool s3eVungleSetCustomCountDownText_platform(const char* text)
{
    NSString* nsText = [[NSString alloc] initWithUTF8String:text];
    s3eBool ret = [VGVunglePub setCustomCountDownText:nsText];
    [nsText release];

    return ret;
}

void s3eVungleSetAlertBoxSettings_platform(const char* title, const char* body, const char* leftButtonTitle, const char* rightButtonTitle)
{
    NSString *nsTitle = [[NSString alloc] initWithUTF8String:title];
    NSString *nsBody = [[NSString alloc] initWithUTF8String:body];
    NSString *nsLeftButton = [[NSString alloc] initWithUTF8String:leftButtonTitle];
    NSString *nsRightButton = [[NSString alloc] initWithUTF8String:rightButtonTitle];
    [VGVunglePub alertBoxWithTitle:nsTitle Body:nsBody leftButtonTitle:nsLeftButton rightButtonTitle:nsRightButton];
    [nsTitle release];
    [nsBody release];
    [nsLeftButton release];
    [nsRightButton release];
}

void s3eVungleSetAllowAutoRotate_platform(s3eBool allow)
{
    [VGVunglePub allowAutoRotate:allow];
}

void s3eVungleSetBackButtonEnabled_platform(s3eBool isBackButtonEnabled)
{
}