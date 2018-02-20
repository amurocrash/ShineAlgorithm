package com.zhaohui.shinealgorithm;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import com.zhaohui.core.algorithm.AlgorithmBaseSort;
import com.zhaohui.core.algorithm.AlgorithmBinarySearch;
import com.zhaohui.core.algorithm.AlgorithmGraph;
import com.zhaohui.core.algorithm.AlgorithmHeapSort;
import com.zhaohui.core.algorithm.AlgorithmUnionFind;
import com.zhaohui.core.utils.ArrayUtils;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class MainActivity extends AppCompatActivity
{

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		initBaseSort();
		initHeapSort();
		initBinarySearch();
		initUnionFind();
		initGraph();
	}

	enum BaseSort
	{
		BUBBLE, SELECTION, INSERT, MERGE, QUICK, IMPROVED_QUICK
	}
	int currentBaseSort = BaseSort.BUBBLE.ordinal();

	void initBaseSort()
	{
		final TextView textView = (TextView) findViewById(R.id.tv_base_sort);
		Button button = (Button)findViewById(R.id.bt_go_base_sort);
		Spinner spinner = (Spinner)findViewById(R.id.sp_base_sort);
		List<String> list = new ArrayList<>();
		list.add("bubble");
		list.add("selection");
		list.add("insert");
		list.add("merge");
		list.add("quick");
		list.add("improved_quick");
		spinner.setAdapter(
				new ArrayAdapter<String>(
						this,
						android.R.layout.simple_list_item_1,
						android.R.id.text1,
						list));
		spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
		{
			@Override
			public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
			{
				currentBaseSort = position;
			}

			@Override
			public void onNothingSelected(AdapterView<?> parent)
			{
			}
		});

		button.setOnClickListener(new View.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				StringBuilder sb = new StringBuilder();
				int arr[] = ArrayUtils.generateRandomArray(1, 10);

				sb.append("Before sort: " + ArrayUtils.arrayToStr(arr) + "\n\n");
				if(currentBaseSort == BaseSort.BUBBLE.ordinal())
				{
					AlgorithmBaseSort.bubbleSort(arr);
				}
				else if(currentBaseSort == BaseSort.SELECTION.ordinal())
				{
					AlgorithmBaseSort.selectionSort(arr);
				}
				else if(currentBaseSort == BaseSort.INSERT.ordinal())
				{
					AlgorithmBaseSort.insertSort(arr);
				}
				else if(currentBaseSort == BaseSort.MERGE.ordinal())
				{
					AlgorithmBaseSort.mergeSort(arr);
				}
				else if(currentBaseSort == BaseSort.QUICK.ordinal())
				{
					AlgorithmBaseSort.quickSort(arr);
				}
				else if(currentBaseSort == BaseSort.IMPROVED_QUICK.ordinal())
				{
					AlgorithmBaseSort.improvedQuickSort(arr);
				}
				sb.append("After sort: " + ArrayUtils.arrayToStr(arr));

				textView.setText(sb.toString());
			}
		});

	}

	enum HeapSort
	{
		NORMAL, HEAPIFY, INDEX_HEAP
	}

	int currentHeapSort = HeapSort.NORMAL.ordinal();

	void initHeapSort()
	{
		final TextView textView = (TextView) findViewById(R.id.tv_heap_sort);
		Button button = (Button)findViewById(R.id.bt_go_heap_sort);
		Spinner spinner = (Spinner)findViewById(R.id.sp_heap_sort);
		List<String> list = new ArrayList<>();
		list.add("normal");
		list.add("heapify");
		list.add("index_heap");
		spinner.setAdapter(
				new ArrayAdapter<String>(
						this,
						android.R.layout.simple_list_item_1,
						android.R.id.text1,
						list));
		spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
		{
			@Override
			public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
			{
				currentHeapSort = position;
			}

			@Override
			public void onNothingSelected(AdapterView<?> parent)
			{
			}
		});

		button.setOnClickListener(new View.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				StringBuilder sb = new StringBuilder();
				int arr[] = ArrayUtils.generateRandomArray(1, 10);

				sb.append("Before sort: " + ArrayUtils.arrayToStr(arr) + "\n\n");
				if(currentHeapSort == HeapSort.NORMAL.ordinal())
				{
					AlgorithmHeapSort.sortNormal(arr);
				}
				else if(currentHeapSort == HeapSort.HEAPIFY.ordinal())
				{
					AlgorithmHeapSort.sortHeapify(arr);
				}
				else if(currentHeapSort == HeapSort.INDEX_HEAP.ordinal())
				{
					AlgorithmHeapSort.sortIndexHeap(arr);
				}
				sb.append("After sort: " + ArrayUtils.arrayToStr(arr));

				textView.setText(sb.toString());
			}
		});
	}

	enum BS
	{
		baseSearch, searchWithBST, orderTest
	}

	int currentBS = BS.baseSearch.ordinal();

	void initBinarySearch()
	{
		final TextView textView = (TextView)findViewById(R.id.tv_binary_search);
		Spinner spinner = (Spinner)findViewById(R.id.sp_binary_search);
		List<String> list = new ArrayList<>();
		list.add("base binary search");
		list.add("search with BST");
		list.add("orderTest");

		spinner.setAdapter(new ArrayAdapter<String>(
				this,
				android.R.layout.simple_list_item_1,
				android.R.id.text1,
				list
				));
		spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
		{
			@Override
			public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
			{
				currentBS = position;
			}

			@Override
			public void onNothingSelected(AdapterView<?> parent)
			{

			}
		});

		Button button = (Button)findViewById(R.id.bt_go_binary_search);
		button.setOnClickListener(new View.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				if(currentBS == BS.baseSearch.ordinal())
				{

					int[] arr = ArrayUtils.generateRandomArray(0, 10);
					AlgorithmBaseSort.improvedQuickSort(arr);
					int target = new Random().nextInt(10);

					int result =
							AlgorithmBinarySearch.binarySearchBase(arr, target);
					textView.setText(
							"arr is " + ArrayUtils.arrayToStr(arr) + "\n\n" +
									"target is " + target + "\n\n" +
									"index is " + result
					);
				}
				else if(currentBS == BS.searchWithBST.ordinal())
				{
					String value = AlgorithmBinarySearch.searchWithBST(2);
					textView.setText("result of search with bst is " + value);
				}
				else if(currentBS == BS.orderTest.ordinal())
				{
					AlgorithmBinarySearch.orderTest();
				}

			}
		});
	}

	void initUnionFind()
	{
		Button button = (Button)findViewById(R.id.bt_go_union_find);
		button.setOnClickListener(new View.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
			    new Thread(new Runnable()
                {
                    @Override
                    public void run()
                    {
                        AlgorithmUnionFind.unionFindBase();
                        AlgorithmUnionFind.unionFindPro();
                        AlgorithmUnionFind.unionFindProBySize();
                        AlgorithmUnionFind.unionFindProByRank();
                    }
                }).start();

			}
		});
	}

	void initGraph()
	{
		Button button = (Button)findViewById(R.id.bt_go_graph);
		button.setOnClickListener(new View.OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
			    new Thread(new Runnable()
                {
                    @Override
                    public void run()
                    {
                        AlgorithmGraph.test();
                    }

                }).start();

			}
		});
	}

}
