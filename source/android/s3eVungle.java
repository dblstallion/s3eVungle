/*
java implementation of the s3eVungle extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
 
import android.content.Context;
 
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

import com.vungle.sdk.VunglePub;

class s3eVungle
{
	public void onPause()
	{
		VunglePub.onPause();
	}
	public void onResume()
	{
		VunglePub.onResume();
	}
    public void s3eVungleStart(String pubAppID)
    {
		Context context = LoaderActivity.m_Activity;
        VunglePub.init(context, pubAppID);
    }
    public String s3eVungleGetVersionString()
    {
        return VunglePub.getVersionString();
    }
    public boolean s3eVungleIsAdAvailable()
    {
        return VunglePub.isVideoAvailable();
    }
    public void s3eVunglePlayModalAd(boolean animate, boolean showClose)
    {
        VunglePub.displayAdvert();
    }
    public void s3eVunglePlayIncentivizedAd(boolean animate, boolean showClose, String userTag)
    {
        VunglePub.displayIncentivizedAdvert(userTag, showClose);
    }
    public void s3eVungleSetSoundEnabled(boolean enabled)
    {
        VunglePub.setSoundEnabled(enabled);
    }
    public void s3eVungleSetAllowAutoRotate(boolean allow)
    {
        VunglePub.setAutoRotation(allow);
    }
}
