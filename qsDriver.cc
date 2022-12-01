#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <chrono>

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
    return i + 1;
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
    quickSort(arr, 0, arr.size() - 1);
}

vector<double> parse(string inLn)
{
    // Vars
    vector<double> returnVec;
    const string delim = " ";
    size_t pos = 0;
    double temp = 0;
    // Take input line and split at space delimiter
    while ((pos = inLn.find(delim)) != string::npos)
    {
        // Push back parsed double
        temp = stod(inLn.substr(0, pos));
        returnVec.push_back(temp);
        // Delete old data in the line so we can process the next value
        inLn.erase(0, pos + delim.length());
    }
    return returnVec;
}

double average(vector<double> arr)
{
    double ret = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        ret += arr[i];
    }

    return ret/arr.size();
}

int main(int argc, char **argv)
{
    // TODO: File Input, File Output, exec time, etc.
    vector<vector<double>> input;
    vector<double> times10;
    vector<double> times100;
    vector<double> times1000;

    if (argc <= 1)
    {
        cout << "Please specify a file or files that you want to process as an argument. Example:\n./qsDriver 1_10Floats.txt";
    }

    // Import input, Possibly create map to associate file?
    for (int i = 1; i < argc; i++)
    {
        // Open Files, Grab Lines
        ifstream reader(argv[i]);
        string line;
        if (reader.is_open() && reader.good())
        {
            getline(reader, line);
        }
        else
        {
            continue;
        }

        input.push_back(parse(line)); // Push back new input vector

        // Close stream for next input
        reader.close();
    }
    cout << input.size() << endl;

    for (int i = 0; i < input.size(); i++)
    {
        cout << "File " << i + 1 << endl;
        for (int j = 0; j < input[i].size(); j++)
        {
            cout << "Value " << j + 1 << ": " << input[i][j] << endl;
        }
    }

    // Process Input, Log time to a "times" file
    for (int i = 0; i < input.size(); i++)
    {
        for (int i = 0; i < input[i].size(); i++)
        {
            cout << input[i].size() << "    ";
            double tempTime = 0;

            // Start time
            auto start = chrono::steady_clock::now();
            // Quicksort run on first files contents
            quickSort(input[i]);
            // End Time
            auto end = chrono::steady_clock::now();
            tempTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            cout << tempTime << endl;

            switch (input[i].size())
            {
            case 10:
                times10.push_back(tempTime);

            case 100:
                times100.push_back(tempTime);

            case 1000:
                times1000.push_back(tempTime);
            }
        }

        cout << "input size    avg time" << endl;
        cout << "10    " << average(times10) << endl;
        cout << "input size    avg time" << endl;
        cout << "100    " << average(times100) << endl;
        cout << "input size    avg time" << endl;
        cout << "1000    " << average(times100) << endl;
    }

    // Go through vectors
    return 0;
}
