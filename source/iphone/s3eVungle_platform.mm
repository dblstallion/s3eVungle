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

// Asset loader
@interface VGFileAssetLoader : NSObject <VGAssetLoader>
- (NSData*)vungleLoadAsset:(NSString*)path;
- (UIImage*)vungleLoadImage:(NSString*)path;
@end

@implementation VGFileAssetLoader
- (NSData*)vungleLoadAsset:(NSString*)path
{
	return [NSData dataWithContentsOfFile:path];
}

- (UIImage*)vungleLoadImage:(NSString*)path
{
	NSData* data = [self vungleLoadAsset:path];
	if (data)
    {
		return [UIImage imageWithData:data];
	}
	return nil;
}
@end

s3eResult s3eVungleInit_platform()
{
    VGFileAssetLoader* assetLoader = [[VGFileAssetLoader alloc] init];
    [VGVunglePub setAssetLoader:assetLoader];
    [assetLoader release];

    return S3E_RESULT_SUCCESS;
}

void s3eVungleTerminate_platform()
{
    [VGVunglePub stop];
}

void s3eVungleDefaultUserData_platform(s3eVungleUserData* out_userData)
{
    VGUserData* data = [VGUserData defaultUserData];

    out_userData->age = data.age;
    out_userData->gender = (s3eVungleGender)data.gender;
    out_userData->adOrientation = (s3eVungleAdOrientation)data.adOrientation;
    out_userData->locationEnabled = data.locationEnabled;
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
	[VGVunglePub startWithPubAppID:[NSString stringWithUTF8String:pubAppID]];
}

void s3eVungleStartWithUserData_platform(const char* pubAppID, const s3eVungleUserData* userData)
{
    VGUserData* data = [VGUserData defaultUserData];

    data.age = userData->age;
    data.gender = (VGGender)userData->gender;
    data.adOrientation = (VGAdOrientation)userData->adOrientation;
    data.locationEnabled = userData->locationEnabled;

    [VGVunglePub startWithPubAppID:[NSString stringWithUTF8String:pubAppID] userData:data];
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
    [VGVunglePub playIncentivizedAd:viewController animated:animate showClose:showClose userTag:[NSString stringWithUTF8String:userTag]];
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
    return [VGVunglePub setCustomCountDownText:[NSString stringWithUTF8String:text]];
}

void s3eVungleSetAlertBoxSettings_platform(const char* title, const char* body, const char* leftButtonTitle, const char* rightButtonTitle)
{
    [VGVunglePub alertBoxWithTitle:[NSString stringWithUTF8String:title] Body:[NSString stringWithUTF8String:body] leftButtonTitle:[NSString stringWithUTF8String:leftButtonTitle] rightButtonTitle:[NSString stringWithUTF8String:rightButtonTitle]];
}

void s3eVungleSetAllowAutoRotate_platform(s3eBool allow)
{
    [VGVunglePub allowAutoRotate:allow];
}
