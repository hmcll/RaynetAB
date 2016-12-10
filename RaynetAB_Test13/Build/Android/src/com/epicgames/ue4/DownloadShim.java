package com.epicgames.ue4;

import com.YourCompany.RaynetAB_Test13.OBBDownloaderService;
import com.YourCompany.RaynetAB_Test13.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

