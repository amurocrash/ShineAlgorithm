package com.zhaohui.core.utils;

import java.util.Random;

/**
 * Created by Amuro on 2018/1/24.
 */

public class ArrayUtils
{
	public static String arrayToStr(int[] arr)
	{
		if(arr == null || arr.length == 0)
		{
			return "empty array";
		}

		StringBuilder sb = new StringBuilder();

		for(int i = 0; i < arr.length; i++)
		{
			if(i == arr.length - 1)
			{
				sb.append(arr[i]);
				break;
			}

			sb.append(arr[i] + ", ");
		}

		return sb.toString();
	}

	public static int[] generateRandomArray(int min, int max)
	{
		Random random = new Random();
		int length = random.nextInt(max - min + 1) + min;
		int array[] = new int[length];
		for(int i = 0; i < length; i++)
		{
			int x = random.nextInt(length);
			array[i] = x;
		}

		return array;
	}
}
