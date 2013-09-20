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
    data.adOrientation = s3eVungleAdOrientationPortrait;
    data.locationEnabled = true;

    // Settings
    s3eVungleSetAlertBoxSettings("Stop?", "You won't get your reward, man", "Stop!", "I want it");
    s3eVungleSetAllowAutoRotate(true);
    s3eVungleSetCacheSize(30);
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
        if(s3eVungleIsAdAvailable())
        {
            s3eDebugOutputString("Ad available, playing");
            s3eVunglePlayModalAd(true, true);
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