#include "s3eOSReadString.h"
#include "s3eVungle.h"
#include "IwDebug.h"
#include "IwGx.h"
#include "s3eExt.h"
#include "s3ePointer.h"
#include "s3eFile.h"
#include "s3eSurface.h"
#include <string>
#include <sstream>

void vungleMoviePlayed(s3eVunglePlayData *playData, void *userData)
{
    s3eDebugOutputString("Vungle movie played");
    printf("movieTotal: %f, movieViewed: %f, playedFull: %d, start: %f\n", playData->movieTotal, playData->movieViewed, playData->playedFull, playData->start);
}

void vungleStatusUpdate(s3eVungleStatusData *statusData, void *userData)
{
    s3eDebugOutputString("Vungle status update");
    printf("status: %d, videoAdsCached: %d, videoAdsUnviewed: %d\n", statusData->status, statusData->videoAdsCached, statusData->videoAdsUnviewed);
}

void vungleViewDidDisappear(void *statusData, void *userData)
{
    s3eDebugOutputString("Vungle view did disappear");
}

void vungleViewWillAppear(void *statusData, void *userData)
{
    s3eDebugOutputString("Vungle view will appear");
}

void vungleAppStoreViewDidDisappear(void *statusData, void *userData)
{
    s3eDebugOutputString("Vungle app store view did disappear");
}

void vungleAppStoreWillAppear(void *statusData, void *userData)
{
    s3eDebugOutputString("Vungle app store view will appear");
}

void initVungle()
{
    IW_CALLSTACK("initVungle");

    if (!s3eVungleAvailable())
    {
        s3eDebugOutputString("Can't load Vungle");
        s3eDebugOutputString(s3eExtGetErrorString());
        return;
    }

    s3eVungleUserData data;
    s3eVungleDefaultUserData(&data);
    data.adOrientation = s3eVungleAdOrientationLandscape;
    data.locationEnabled = true;

    s3eVungleRegister(s3eVungleCallback_MoviePlayed, (s3eCallback)vungleMoviePlayed, NULL);
    s3eVungleRegister(s3eVungleCallback_StatusUpdate, (s3eCallback)vungleStatusUpdate, NULL);
    s3eVungleRegister(s3eVungleCallback_ViewDidDisappear, (s3eCallback)vungleViewDidDisappear, NULL);
    s3eVungleRegister(s3eVungleCallback_ViewWillAppear, (s3eCallback)vungleViewWillAppear, NULL);
    s3eVungleRegister(s3eVungleCallback_AppStoreViewDidDisappear, (s3eCallback)vungleAppStoreViewDidDisappear, NULL);
    s3eVungleRegister(s3eVungleCallback_AppStoreWillAppear, (s3eCallback)vungleAppStoreWillAppear, NULL);

    // Settings
    s3eVungleSetAlertBoxSettings("Stop?", "You won't get your reward, man", "Stop!", "I want it");
    s3eVungleSetAllowAutoRotate(false);
    s3eVungleSetCacheSize(10);
    s3eVungleSetCustomCountDownText("Your reward");
    s3eVungleSetLogToStdout(true);
    s3eVungleSetSoundEnabled(true);
    s3eVungleSetMuteIfMusicIsPlaying(false);

    s3eVungleStartWithUserData("523882d90f85ef927a00000a", &data);

    s3eDebugOutputString("Successfully started Vungle extension");
    s3eDebugOutputString(s3eVungleGetVersionString());
}

void buttonEvent(s3ePointerTouchEvent *event)
{
    IW_CALLSTACK("buttonEvent");

    if(event->m_Pressed)
    {
        if(event->m_x < 400)
        {
            if(s3eVungleIsAdAvailable())
            {
				s3eDebugOutputString("s3eVunglePlayModalAd");
                s3eVunglePlayModalAd(true, true);
            }
            else
            {
                s3eDebugOutputString("No ad available");
            }
        }
        else
        {
			s3eDebugOutputString("s3eVunglePlayIncentivizedAd");
            s3eVunglePlayIncentivizedAd(true, true, NULL);
        }
    }
}

// Example showing how to use the s3eWwise extension
int main()
{
    IW_CALLSTACK("main");

    s3eDebugOutputString("Booting Vungle example");

    initVungle();

    s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)buttonEvent, NULL);

    IwGxInit();

    IwGxSetColClear(0, 0, 0, 0xff);

    while(!s3eDeviceCheckQuitRequest())
    {
        std::stringstream str;

        IwGxClear();

        IwGxPrintString(100, 100, "s3eVungle");

        IwGxPrintString(100, 300, "Touch to show ad");

        IwGxFlush();
        IwGxSwapBuffers();
        s3eDeviceYield(0);
    }

    IwGxTerminate();

    s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)buttonEvent);

    return 0;
}