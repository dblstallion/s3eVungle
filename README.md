s3eVungle
=========

This is the official Maramalade extension for [Vungle](http://www.vungle.com/).
Vungle allows you to play video ads in your game (incentivized and interstitial).

Pre-compiled binaries are provided on GitHub. Instructions on how to compile
the extension are listed below.

Supported Platforms
-------------------

* iOS
* Android

Building s3eVungle
==================

As you build the library for each platform, make sure to follow the [EDK Guide](http://docs.madewithmarmalade.com/display/MD700/Extensions+Development+Kit+EDK).

Android
-------

On Android, make sure you have the Android SDK and NDK installed. These can be extracted anywhere on the drive.
Make sure you have an environment variable called NDK_ROOT which points to the NDK installation folder.

Double-click the `s3eVungle_android.mkb` file to launch the native build and `s3eVungle_android_java.mkb` for the java build.

iOS
---

The iOS extension must be built on a Mac. The easiest way to do this is to share the Marmalade/<version>/extensions
folder and mount it on your Mac. Instructions to do this can be found in the [iOS EDK Guide](http://developer.roolez.com/marmaladesdk/main/native/extensions/edkguides/iosedkguide.html)

Make sure you have the Marmalade SDK installed on your Mac, along with all its dependencies.

Build the extension in the terminal by navigating to the s3eVungle folder and running `mkb --arm --iphone s3eVungle_iphone.mkb`.

Implementation Example
======================

An example of how to use s3eVungle is provided in the `s3eVungle/example` directory. This is a standard Marmalade application
and is configured exactly the way your project should be when using s3eVungle.

Building the Example
--------------------

To build the example, begin by double-clicking the `example/s3eVungleExample.mkb` file. Build the project for ARM and deploy
it as you would any other Marmalade application to produce an IAP or APK.

Tapping on the screen will request that a video be played. If a video is available, it will take over the application and play.

Deploying the Example
---------------------

To test the different platform versions of the extension, you must deploy the example to a device. To do this use the Marmalade Deploy Tool.
You can follow instructions on how to deploy to each device in the [Marmalade Documentation](http://docs.madewithmarmalade.com/display/MD700/iOS+platform+guide#iOSplatformguide-DeploytoiOSDeployingtoiOS).
