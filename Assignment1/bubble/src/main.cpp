#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void SelectionSort(int arr[], int size);
void swap(int* x, int* y);
void Print(int arr[], int size);
void InsertionSort(int arr[], int size);

int main()
{
	int arr[7] = { 1,9,2,4,5,8,7 };
	cout << "Array: ";
	Print(arr, 7);
	
	InsertionSort(arr, 7);
	cout << "\nSorted array: ";
	Print(arr,7);

	cin.get();
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void SelectionSort(int arr[], int size)
{
	int min = 0;
	for (int i = 0; i < size-1; i++)
	{
		 min = i;
		for (int j = i+1; j < size ; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
			swap(&arr[i], &arr[min]);
		}
	}
}

void Print(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ", ";
	}

}

void InsertionSort(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int move = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > move)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = move;
	}
}