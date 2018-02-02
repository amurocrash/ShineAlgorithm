package com.zhaohui.core.utils;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by Amuro on 2018/1/30.
 */

public class ToastUtils
{
	public static void show(Context context, String msg)
	{
		Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
	}
}
