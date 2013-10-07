/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
/*
 * This file contains the automatically generated loader-side
 * functions that form part of the extension.
 *
 * This file is awlays compiled into all loaders but compiles
 * to nothing if this extension is not enabled in the loader
 * at build time.
 */
#include "IwDebug.h"
#include "s3eVungle_autodefs.h"
#include "s3eEdk.h"
#include "s3eVungle.h"
//Declarations of Init and Term functions
extern s3eResult s3eVungleInit();
extern void s3eVungleTerminate();


// On platforms that use a seperate UI/OS thread we can autowrap functions
// here.   Note that we can't use the S3E_USE_OS_THREAD define since this
// code is oftern build standalone, outside the main loader build.
#if defined I3D_OS_IPHONE || defined I3D_OS_OSX || defined I3D_OS_LINUX || defined I3D_OS_WINDOWS

static void s3eVunglePlayModalAd_wrap(s3eBool animate, s3eBool showClose)
{
    IwTrace(VUNGLE_VERBOSE, ("calling s3eVungle func on main thread: s3eVunglePlayModalAd"));
    s3eEdkThreadRunOnOS((s3eEdkThreadFunc)s3eVunglePlayModalAd, 2, animate, showClose);
}

static void s3eVunglePlayIncentivizedAd_wrap(s3eBool animate, s3eBool showClose, const char* userTag)
{
    IwTrace(VUNGLE_VERBOSE, ("calling s3eVungle func on main thread: s3eVunglePlayIncentivizedAd"));
    s3eEdkThreadRunOnOS((s3eEdkThreadFunc)s3eVunglePlayIncentivizedAd, 3, animate, showClose, userTag);
}

#define s3eVunglePlayModalAd s3eVunglePlayModalAd_wrap
#define s3eVunglePlayIncentivizedAd s3eVunglePlayIncentivizedAd_wrap

#endif

void s3eVungleRegisterExt()
{
    /* fill in the function pointer struct for this extension */
    void* funcPtrs[21];
    funcPtrs[0] = (void*)s3eVungleDefaultUserData;
    funcPtrs[1] = (void*)s3eVungleRegister;
    funcPtrs[2] = (void*)s3eVungleUnRegister;
    funcPtrs[3] = (void*)s3eVungleStart;
    funcPtrs[4] = (void*)s3eVungleStartWithUserData;
    funcPtrs[5] = (void*)s3eVungleGetCurrentStatusData;
    funcPtrs[6] = (void*)s3eVungleIsRunning;
    funcPtrs[7] = (void*)s3eVunglePrintCacheFiles;
    funcPtrs[8] = (void*)s3eVunglePrintDeviceSettings;
    funcPtrs[9] = (void*)s3eVungleGetVersionString;
    funcPtrs[10] = (void*)s3eVungleIsAdAvailable;
    funcPtrs[11] = (void*)s3eVunglePlayModalAd;
    funcPtrs[12] = (void*)s3eVunglePlayIncentivizedAd;
    funcPtrs[13] = (void*)s3eVungleGetCacheSize;
    funcPtrs[14] = (void*)s3eVungleSetCacheSize;
    funcPtrs[15] = (void*)s3eVungleSetLogToStdout;
    funcPtrs[16] = (void*)s3eVungleSetSoundEnabled;
    funcPtrs[17] = (void*)s3eVungleSetMuteIfMusicIsPlaying;
    funcPtrs[18] = (void*)s3eVungleSetCustomCountDownText;
    funcPtrs[19] = (void*)s3eVungleSetAlertBoxSettings;
    funcPtrs[20] = (void*)s3eVungleSetAllowAutoRotate;

    /*
     * Flags that specify the extension's use of locking and stackswitching
     */
    int flags[21] = { 0 };

    /*
     * Register the extension
     */
    s3eEdkRegister("s3eVungle", funcPtrs, sizeof(funcPtrs), flags, s3eVungleInit, s3eVungleTerminate, 0);
}

#if !defined S3E_BUILD_S3ELOADER

#if defined S3E_EDK_USE_STATIC_INIT_ARRAY
int s3eVungleStaticInit()
{
    void** p = g_StaticInitArray;
    void* end = p + g_StaticArrayLen;
    while (*p) p++;
    if (p < end)
        *p = (void*)&s3eVungleRegisterExt;
    return 0;
}

int g_s3eVungleVal = s3eVungleStaticInit();

#elif defined S3E_EDK_USE_DLLS
S3E_EXTERN_C S3E_DLL_EXPORT void RegisterExt()
{
    s3eVungleRegisterExt();
}
#endif

#endif
