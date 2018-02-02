package com.zhaohui.shinealgorithm;

import android.app.Application;

/**
 * Created by Amuro on 2018/1/23.
 */

public class AlgorithmApp extends Application
{
	static
	{
		System.loadLibrary("shine-algorithm-lib");
	}

	@Override
	public void onCreate()
	{
		super.onCreate();
	}
}
