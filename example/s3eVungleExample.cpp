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

    s3eDebugOutputString("Successfully loaded Vungle extension");
}

void buttonEvent(s3ePointerTouchEvent *event)
{
    IW_CALLSTACK("buttonEvent");

    if(event->m_Pressed)
    {
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