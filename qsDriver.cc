#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int partition(vector<double> &arr, int low, int high)
{
    // Select Pivot
    double pivot = arr[high];
    int i = (low - 1);
    double temp = 0;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i+1;
}

void quickSort(vector<double> &arr, int low, int high)
{
    if (low < high)
    {
        int pIndex = partition(arr, low, high);
        quickSort(arr, low, pIndex - 1);
        quickSort(arr, pIndex + 1, high);
    }
}

void quickSort(vector<double> &arr)
{
    quickSort(arr, 0, arr.size()-1);
}



int main(int argc, char **argv)
{
    // cout << genRandInt(1, 5000) << endl;
    // cout << genRandFloat() << endl;

    // Create test VECTOR of floats
    vector<double> testArr = {1.23432, 335.1212, 23.9816, 999.295, 27.001, 27.002, 27.000, 0.11235};

    // Print test array
    cout << "Test Array: " << endl;
    for (int i = 0; i < testArr.size(); i++)
    {
        cout << testArr[i] << " ";
    }

    // Quicksort test array
    quickSort(testArr);
    cout << endl;

    // Print sorted test array
    cout << "Sorted Array: " << endl;
    for (int i = 0; i < testArr.size(); i++)
    {
        cout << testArr[i] << " ";
    }
    cout << endl;

    //TODO: Process Args, File Input, File Output, exec time, etc.

}
