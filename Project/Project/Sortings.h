#pragma once
#include <fstream>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <cstdlib>

using namespace std;


class Sortings
{
public:
	int* arr = new int[8000];
	ofstream writeFile;
	Sortings(bool flag)
	{
		if (flag) {
			writeFile.open("results.csv", ios::out);
			GenerateStandardArray();
			Start();
			writeFile.close();
		}
	}

private:
	// Start

	// Universal function with reference to the sorting function
	void OneSorting(long long (Sortings::* sort)(int*& arr, int n), string sortName, string sortType)
	{
		long long* count = new long long[8];
		Sortings s(false);
		int* testArray;
		// Creating arrays 1000..8000
		for (int i = 1; i < 9; i++) {
			long long t = 0;
			testArray = new int[i * 1000];
			GetElements(testArray, i * 1000);
			count[i - 1] = (s.*sort)(testArray, i * 1000);
		}
		WriteToCSV(count, sortName, sortType);
		delete[] count;
		delete[] testArray;
	}

	// Running each type of sort
	void StartEachType(string sortType)
	{
		OneSorting(&Sortings::DefaultBubbleSort, "DefaultBubbleSort", sortType);
		OneSorting(&Sortings::BubbleSort1, "BubbleSort1", sortType);
		OneSorting(&Sortings::BubbleSort2, "BubbleSort2", sortType);
		OneSorting(&Sortings::Insert, "Insert", sortType);
		OneSorting(&Sortings::BinInsert, "BinInsert", sortType);
		OneSorting(&Sortings::CountSort, "CountSort", sortType);
		OneSorting(&Sortings::radixSort, "radixSort", sortType);
	}

	// Start of the algo
	// Generating different arrays
	void Start()
	{
		GenerateStandardArray();
		StartEachType("случайные значения от 0 до 9");
		GenerateBigArray();
		StartEachType("от 0 до 10000");
		GenerateSemiSortedArray();
		StartEachType("«Почти» отсортированный массив");
		GenerateReverseSortedArray();
		StartEachType("Отсортированный в обратном порядке числами от 10000 до 1");
	}

	//Other methods

	//Creating CSV output file
	void WriteToCSV(long long* count, string sortName, string sortType)
	{
		writeFile << ";" << (sortName + " " + sortType).c_str() << endl;
		for (int i = 1; i < 9; i += 1)
			writeFile << i * 1000 << ";" << count[i - 1] << endl;
	}

	//Creating array with given size from standrad array
	void GetElements(int*& mas, long long count)
	{
		for (int i = 0; i < count; i++)
			mas[i] = arr[i];
	}


	// Array generation

	// Creating array of [0..9]
	void GenerateStandardArray()
	{
		srand((unsigned)time(NULL));
		for (int i = 0; i < 8000; i++)
			arr[i] = rand() % 10;
	}

	// Creating array of [0..10000]
	void GenerateBigArray()
	{
		srand((unsigned)time(NULL));
		for (int i = 0; i < 8000; i++)
			arr[i] = rand() % 10001;
	}

	// Creating semi-sorted array
	void GenerateSemiSortedArray()
	{
		for (int i = 0; i < 8000; i++)
			arr[i] = i;
		swap(arr[4], arr[1234]);
		swap(arr[15], arr[3284]);
		swap(arr[123], arr[5836]);
		swap(arr[7640], arr[934]);
		swap(arr[1789], arr[5138]);
	}

	// Creating reversed sorted array
	void GenerateReverseSortedArray()
	{
		for (int i = 0; i < 8000; i++)
			arr[i] = 8000 - i;
	}

	// Some sorting methods

	// Max in array
	int MaxInArray(int* a, int n, long long& count) {
		int max = a[0];
		count += 2; // max = a[0]
		count += 2; // i = 1; i < n
		for (int i = 1; i < n; i++) {
			count += 3; // i < n; i++
			count += 2; // max < a[i]
			if (max < a[i])
			{
				max = a[i];
				count += 2; // max = a[i]
			}
		}
		return max;
	}

	// Min in array
	int MinInArray(int* a, int n, long long& count) {
		int min = a[0];
		count += 2; // min = a[0]
		count += 2; // i = 1; i < n
		for (int i = 1; i < n; i++) {
			count += 3; // i < n; i++
			count += 2; // min > a[i]
			if (min > a[i])
			{
				min = a[i];
				count += 2; // min = a[i]
			}
		}
		return min;
	}


	union RadixUnion {
		unsigned int num;
		unsigned char set[4];
	};

	// Binary search
	int BinSearch(int* arr, int key, int left, int right, long long& count) {
		int l = left;
		int r = right;
		count += 2; // l = left; r = right
		int m;
		count += 2; // l < r - 1
		while (l < r - 1)
		{
			m = (l + r) / 2;
			count += 3; // m = (l + r) / 2
			count += 2; // arr[m] <= key
			if (arr[m] <= key) {
				l = m;
				count += 1; // l = m
			}
			else {
				r = m;
				count += 1; // r = m
			}
		}
		return l;
	}



	// Sort

	long long DefaultBubbleSort(int*& arr, int n) {
		int len = n - 1;
		long long count = 4; // len = n - 1; i = 0; i < len
		for (int i = 0; i < len; i++)
		{
			count += 3; // i < len; i++
			count += 4; // j = 0; j < n - i - 1
			for (int j = 0; j < n - i - 1; j++)
			{
				count += 5; // j < n - i - 1; j++
				count += 4; // arr[j] > arr[j + 1]
				if (arr[j] > arr[j + 1]) {
					count += 9; // swap
					std::swap(arr[j], arr[j + 1]);
				}
			}
		}
		return count;
	}


	long long BubbleSort1(int*& arr, int n) {
		int i = 0;
		bool flag = true;
		long long count = 3; // flag = true; i = 0; while (flag)
		while (flag) {
			flag = false;
			count += 5; // flag = false; j = 0; j < n - i - 1
			for (int j = 0; j < n - i - 1; j++) {
				count += 5; // j < n - i - 1; j++
				count += 4; // arr[j] > arr[j + 1]
				if (arr[j] > arr[j + 1]) {
					count += 9; // swap
					std::swap(arr[j], arr[j + 1]);
					flag = true;
					count += 1; // flag = true
				}
			}
			i++;
			count += 2; // i++
		}
		return count;
	}


	long long BubbleSort2(int*& arr, int n) {		
		int bound = n;
		int count = 1; // bound = n
		int t;
		do
		{			
			t = 0;
			count += 1; // t = 0
			int len = bound - 1;
			count += 2; // len = bound - 1;
			count += 2; // i = 0; i < len
			for (int i = 0; i < len; i++)
			{
				count += 3; // i < len; i++
				count += 4; // arr[i] < arr[i + 1] 
				if (arr[i] < arr[i + 1])
				{
					count += 9; // swap
					swap(arr[i], arr[i + 1]);
					t = i;
					count += 1; // t = i
				}
			}
			bound = t + 1;
			count += 2; // bound = t + 1
			count += 1; // t != 0
		} while (t != 0);
		return count;
	}


	long long Insert(int*& arr, int n) {
		int j = 0;
		long long count = 1; // j = 0
		count += 2; // i = 1; i < n
		for (int i = 1; i < n; i++) {
			count += 3; // i < n; i++
			count += 6; // j = i; j > 0 && arr[j - 1] > arr[j]
			for (j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
				count += 7; // j > 0 && arr[j - 1] > arr[j]; j--
				count += 9; // swap
				std::swap(arr[j - 1], arr[j]);
			}
		}
		return count;
	}


	long long BinInsert(int*& arr, int n) {
		int j, k;
		long long count = 2; // i = 1; i < n
		for (int i = 1; i < n; i++) {
			count += 3; // i < n; i++
			j = i - 1;
			count += 2; // j = i - 1
			k = BinSearch(arr, arr[i], 0, j, count);
			count += 2; // k = BinSearch(arr, arr[i], 0, j, count);
			count += 3; // arr[k] <= arr[i]
			if (arr[k] <= arr[i]) {
				k++;
				count += 2; // k++
			}
			count += 3; // arr[k] <= arr[i]
			if (arr[k] <= arr[i]) {
				k++;
				count += 2; // k++
			}
			count += 2; // m = j; m >= k
			for (int m = j; m >= k; --m) {
				count += 3; // m >= k; --m
				count += 9; // swap
				std::swap(arr[m], arr[m + 1]);
			}
		}
		return count;
	}


	long long CountSort(int*& arr, int n) {
		long long count = 0;
		int max = MaxInArray(arr, n, count);
		int min = MinInArray(arr, n, count);
		count += 2; // max = MaxInArray(arr, n, count); min = MinInArray(arr, n, count)
		int k = max - min + 1;
		count += 3; // k = max - min + 1;
		int* c = new int[k];
		count += 3; // *c = new int[k]; i = 0; i < k
		for (int i = 0; i < k; i++) {
			c[i] = 0;
			count += 2; // c[i] = 0;
		}
		count += 2; // i = 0; i < n
		for (int i = 0; i < n; i++) {
			c[arr[i] - min]++;
			count += 5; // c[arr[i] - min]++;
		}
		int pos = 0;
		count += 3; // pos = 0; j = 0; j < k
		for (int j = 0; j < k; j++) {
			count += 3; // j < k; j++
			count += 3; // i = 0; i < c[j]
			for (int i = 0; i < c[j]; i++) {
				count += 4; // i < c[j]; i++
				arr[pos++] = j + min;
				count += 5; // arr[pos++] = j + min
			}
		}
		delete[] c;
		return count;
	}


	long long radixSort(int*& arr, int n)
	{
		int digit = 0;
		long long count = 1; // digit = 0
		RadixUnion* temp = new RadixUnion[n];
		count += 1; // RadixUnion *temp = new RadixUnion[n]

		count += 1; // digit < 4
		while (digit < 4) {
			count += 2; // i = 0; i < n
			for (int i = 0; i < n; i++) {
				count += 3; // i < n; i++
				temp[i].num = (unsigned int)arr[i];
				count += 4; // temp[i].num = (unsigned int)arr[i]
			}

			int* c = new int[256];
			count += 1; // *c = new int[256]

			count += 2; // i = 0; i < 256
			for (int i = 0; i < 256; i++) {
				count += 3; // i < 256; i++
				c[i] = 0;
				count += 2; // c[i] = 0
			}

			count += 2; // i = 0; i < n
			for (int i = 0; i < n; i++) {
				count += 3; // i < n; i++
				c[temp[i].set[digit]]++;
				count += 6; // c[temp[i].set[digit]]++
			}


			long long k = 0, j;
			count += 1; // k = 0

			count += 2; // i = 0; i < 256
			for (int i = 0; i < 256; i++) {
				count += 3; // i < 256; i++
				j = c[i];
				c[i] = k;
				k += j;
				count += 6; // j = c[i]; c[i] = k; k += j
			}

			count += 2; // i = 0; i < n
			for (int i = 0; i < n; i++) {
				count += 3; // i < n; i++
				int tempIndex = temp[i].set[digit];
				count += 4; // tempIndex = temp[i].set[digit]
				arr[c[tempIndex]] = temp[i].num;
				count += 5; // arr[c[tempIndex]] = temp[i].num
				c[tempIndex]++;
				count += 3; // c[tempIndex]++
			}

			digit++;
			count += 2; // digit++
			delete[] c;
		}

		delete[] temp;
		return count;
	}

};
