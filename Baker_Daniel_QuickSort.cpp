#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
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

    return ret / arr.size();
}

int main(int argc, char **argv)
{
    // TODO: File Input, File Output, exec time, etc.
    vector<vector<double>> input;
    vector<double> times10 = {};
    vector<double> times100 = {};
    vector<double> times1000 = {};
    vector<string> filenames = {"executionTime.txt", "averageExecutionTime.txt", "sortedArrs.txt"};

    // File Streams

    if (argc <= 1)
    {
        cout << "Not enough arguments\nUsage Example: ./QuickSort 1_10Floats.txt" << endl
        << "Usage Example with Input and Output flags: ./QuickSort -i 1_10Floats.txt -o execTime.txt avgExecTime.txt sortedArrs.txt" << endl
        << endl << "For more information, please check the README." << endl;
    }
    // Create conditional to find -o flag, mark pos and process input, create ostreams
    int outStart = -1;
    for (int i = 0; i < argc; i++)
    {
        if (string(argv[i]) == "-o" || string(argv[i]) == "--output")
        {
            outStart = i;
        }
    }

    // if no output flag, assume all files are input
    if (outStart == -1)
    {
        outStart = argc;
    }
    else if (outStart > 0)
    {
        filenames.clear();
        for (int i = outStart + 1; i < argc; i++)
        {
            filenames.push_back(string(argv[i]));
        }
    }

    // Import input
    for (int i = 1; i < outStart; i++)
    {
        // Open Files, Grab Lines
        ifstream reader(argv[i]);
        string line;
        if (reader.is_open() && reader.good() && string(argv[i]) != "-i")
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

    // First output will go to exec time

    ofstream outOne(filenames[0]);
    outOne << "input size    Execution Time (ns)" << endl;
    // Process Input, Log time to a "times" file
    for (int i = 0; i < input.size(); i++)
    {
        // Start time
        auto start = chrono::steady_clock::now();
        // Quicksort run on first files contents
        quickSort(input[i]);
        // End Time
        auto end = chrono::steady_clock::now();
        auto tempTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        // cout << input[i].size();
        switch (input[i].size())
        {
        case 10:
            times10.push_back(tempTime);
            break;

        case 100:
            times100.push_back(tempTime);
            break;

        case 1000:
            times1000.push_back(tempTime);
            break;
        }

        outOne << input[i].size() << "    " << tempTime << endl;
    }

    outOne.close();
    // cout << "RUN NO. " << i+1 << "\n--------------------------------" << endl;

    // Avg. Times File Output
    ofstream outTwo(filenames[1]);
    outTwo << "Input Size    Average Execution Time (ns)" << endl;
    if (!times10.empty())
    {
        outTwo << "10    " << to_string(average(times10)) << endl;
    }

    if (!times100.empty())
    {
        outTwo << "100    " << to_string(average(times100)) << endl;
    }
    if (!times1000.empty())
    {
        outTwo << "1000    " << to_string(average(times1000));
    }

    outTwo.close();

    // Make a folder, put sorted arr files there
    filesystem::create_directories("Sorted");
    for (int i = 0; i < input.size(); i++)
    {
        ofstream temp("./Sorted/" + to_string(i + 1) + +"_" + filenames[2]);
        for (int j = 0; j < input[i].size(); j++)
        {
            temp << input[i][j] << " ";
        }
    }

    // Go through vectors
    return 0;
}
