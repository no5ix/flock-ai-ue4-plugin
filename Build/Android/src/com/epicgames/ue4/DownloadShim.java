package com.epicgames.ue4;

import com.YourCompany.MyFish.OBBDownloaderService;
import com.YourCompany.MyFish.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

