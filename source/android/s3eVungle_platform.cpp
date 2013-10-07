/*
 * android-specific implementation of the s3eVungle extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eVungle_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static char* g_RetStr = NULL;
static int g_RetStrLen = 32;

const char* getCString(jstring str)
{
	 if (!str)
        return NULL;
	
    const char* res = s3eEdkGetStringUTF8Chars(str);
	
    g_RetStrLen = strlen(res) + 1;
    g_RetStr = (char *)s3eEdkReallocOS(g_RetStr, g_RetStrLen);
    strcpy(g_RetStr, res);
	
    s3eEdkReleaseStringUTF8Chars(res);
	
    return g_RetStr;
}

static jobject g_Obj;
static jmethodID g_s3eVungleStart;
static jmethodID g_s3eVungleGetVersionString;
static jmethodID g_s3eVungleIsAdAvailable;
static jmethodID g_s3eVunglePlayModalAd;
static jmethodID g_s3eVunglePlayIncentivizedAd;
static jmethodID g_s3eVungleSetSoundEnabled;
static jmethodID g_s3eVungleSetAllowAutoRotate;

static jmethodID g_onPause;
static jmethodID g_onResume;

int32 applicationPaused(void* systemData, void* userData)
{
	JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_onPause);
	return 0;
}

int32 applicationResumed(void* systemData, void* userData)
{
	JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_onResume);
	return 0;
}

static void s3eVungle_StartCallback(JNIEnv *env, jobject _this);
static void s3eVungle_EndCallback(JNIEnv *env, jobject _this);
static void s3eVungle_ViewCallback(JNIEnv *env, jobject _this, double watchedSeconds, double totalSeconds);

s3eResult s3eVungleInit_platform()
{
	//Alloc buffer for returning strings
    g_RetStr = (char*)s3eEdkMallocOS(g_RetStrLen);
	
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;
	
	const JNINativeMethod nativeMethodDefs[] =
    {
        {"StartCallback",	"()V",		(void *)&s3eVungle_StartCallback},
        {"EndCallback",		"()V",		(void *)&s3eVungle_EndCallback},
        {"ViewCallback",	"(DD)V",	(void *)&s3eVungle_ViewCallback},
    };

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3eVungle");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_s3eVungleStart = env->GetMethodID(cls, "s3eVungleStart", "(Ljava/lang/String;)V");
    if (!g_s3eVungleStart)
        goto fail;

    g_s3eVungleGetVersionString = env->GetMethodID(cls, "s3eVungleGetVersionString", "()Ljava/lang/String;");
    if (!g_s3eVungleGetVersionString)
        goto fail;

    g_s3eVungleIsAdAvailable = env->GetMethodID(cls, "s3eVungleIsAdAvailable", "()Z");
    if (!g_s3eVungleIsAdAvailable)
        goto fail;

    g_s3eVunglePlayModalAd = env->GetMethodID(cls, "s3eVunglePlayModalAd", "(ZZ)V");
    if (!g_s3eVunglePlayModalAd)
        goto fail;

    g_s3eVunglePlayIncentivizedAd = env->GetMethodID(cls, "s3eVunglePlayIncentivizedAd", "(ZZLjava/lang/String;)V");
    if (!g_s3eVunglePlayIncentivizedAd)
        goto fail;

    g_s3eVungleSetSoundEnabled = env->GetMethodID(cls, "s3eVungleSetSoundEnabled", "(Z)V");
    if (!g_s3eVungleSetSoundEnabled)
        goto fail;

    g_s3eVungleSetAllowAutoRotate = env->GetMethodID(cls, "s3eVungleSetAllowAutoRotate", "(Z)V");
    if (!g_s3eVungleSetAllowAutoRotate)
        goto fail;

	g_onPause = env->GetMethodID(cls, "onPause", "()V");
    if (!g_onPause)
        goto fail;
		
	g_onResume = env->GetMethodID(cls, "onResume", "()V");
    if (!g_onResume)
        goto fail;
	
	env->RegisterNatives(cls, nativeMethodDefs, sizeof(nativeMethodDefs)/sizeof(nativeMethodDefs[0]));

    IwTrace(VUNGLE, ("VUNGLE init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
	if(s3eDeviceRegister(S3E_DEVICE_UNPAUSE, applicationResumed, NULL) != S3E_RESULT_SUCCESS)
		return S3E_RESULT_ERROR;
		
	if(s3eDeviceRegister(S3E_DEVICE_PAUSE, applicationPaused, NULL) != S3E_RESULT_SUCCESS)
		return S3E_RESULT_ERROR;
		
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3eVungle, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3eVungleTerminate_platform()
{
    // Add any platform-specific termination code here
	s3eEdkFreeOS(g_RetStr);
    g_RetStr = NULL;
	
	s3eDeviceUnRegister(S3E_DEVICE_UNPAUSE, applicationResumed);
	s3eDeviceUnRegister(S3E_DEVICE_UNPAUSE, applicationPaused);
}

static void s3eVungle_StartCallback(JNIEnv *env, jobject _this)
{
	if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_ViewWillAppear))
	{
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_ViewWillAppear);
	}
}

static void s3eVungle_EndCallback(JNIEnv *env, jobject _this)
{
	if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_AppStoreViewDidDisappear))
	{
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_ViewDidDisappear);
	}
}

static void s3eVungle_ViewCallback(JNIEnv *env, jobject _this, double watchedSeconds, double totalSeconds)
{
	if (s3eEdkCallbacksIsRegistered(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_MoviePlayed))
	{
		s3eVunglePlayData pd;
        pd.start = 0;
        pd.movieTotal = totalSeconds;
        pd.movieViewed = watchedSeconds;
        pd.playedFull = watchedSeconds >= totalSeconds;
        s3eEdkCallbacksEnqueue(S3E_EXT_VUNGLE_HASH, s3eVungleCallback_MoviePlayed, &pd, sizeof(pd));
	}
}

void s3eVungleDefaultUserData_platform(s3eVungleUserData* out_userData)
{
	out_userData->age = 0;
	out_userData->gender = s3eVungleGenderUnknown;
	out_userData->adOrientation = s3eVungleAdOrientationUnknown;
	out_userData->locationEnabled = false;
}

void s3eVungleStart_platform(const char* pubAppID)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring pubAppID_jstr = env->NewStringUTF(pubAppID);
    env->CallVoidMethod(g_Obj, g_s3eVungleStart, pubAppID_jstr);
}

void s3eVungleStartWithUserData_platform(const char* pubAppID, const s3eVungleUserData* userData)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring pubAppID_jstr = env->NewStringUTF(pubAppID);
    env->CallVoidMethod(g_Obj, g_s3eVungleStart, pubAppID_jstr);
}

void s3eVungleGetCurrentStatusData_platform(s3eVungleStatusData* out_statusData)
{
    memset(out_statusData, 0, sizeof(*out_statusData));
}

s3eBool s3eVungleIsRunning_platform()
{
    return S3E_TRUE;
}

void s3eVunglePrintCacheFiles_platform()
{
}

void s3eVunglePrintDeviceSettings_platform()
{
}

const char* s3eVungleGetVersionString_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return getCString((jstring)env->CallObjectMethod(g_Obj, g_s3eVungleGetVersionString));
}

s3eBool s3eVungleIsAdAvailable_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eBool)env->CallBooleanMethod(g_Obj, g_s3eVungleIsAdAvailable);
}

void s3eVunglePlayModalAd_platform(s3eBool animate, s3eBool showClose)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eVunglePlayModalAd, animate, showClose);
}

void s3eVunglePlayIncentivizedAd_platform(s3eBool animate, s3eBool showClose, const char* userTag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring userTag_jstr = env->NewStringUTF(userTag);
    env->CallVoidMethod(g_Obj, g_s3eVunglePlayIncentivizedAd, animate, showClose, userTag_jstr);
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
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eVungleSetSoundEnabled, enabled);
}

void s3eVungleSetMuteIfMusicIsPlaying_platform(s3eBool state)
{
}

s3eBool s3eVungleSetCustomCountDownText_platform(const char* text)
{
	return S3E_FALSE;
}

void s3eVungleSetAlertBoxSettings_platform(const char* title, const char* body, const char* leftButtonTitle, const char* rightButtonTitle)
{
}

void s3eVungleSetAllowAutoRotate_platform(s3eBool allow)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eVungleSetAllowAutoRotate, allow);
}
