#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

float genRandDouble(int min, int max)
{
    srand((unsigned)(time(NULL) + rand()));
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

int main(int argc, char **argv)
{
    // Generate a vetor to write to file
    vector<double> write;
    int numFloats = 0;
    int numFiles = 0;

    // Check and see if given args
    if (argc <= 2 || argc > 3)
    {
        cout << "This program requires arguments. This program generates input file(s) for the QuickSort Driver. The generator can be used like this:\n ./fileGen {num_floats} {num_files}" << endl;
        return 1;
    }

    numFloats = stoi(argv[argc - 2]);
    numFiles = stoi(argv[argc - 1]);

    for (int i = 0; i < numFiles; i++)
    {
        ofstream nFile(to_string(i + 1) +"_" + to_string(numFloats) + "Floats.txt");
        for (int j = 0; j < numFloats; j++)
        {
            nFile << to_string(genRandDouble(1, 1000)) + " ";
        }
        nFile << "\n";
        nFile.close();
    }

    return 0;
}