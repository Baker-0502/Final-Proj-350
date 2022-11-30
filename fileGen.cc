#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int genRandInt(int min, int max)
{
    srand((unsigned)time(NULL));
    return min + (rand() % (max - min));
}

float genRandDouble()
{
    srand((unsigned)time(NULL));
    return (double)rand() / (double)RAND_MAX;
}

void main()
{

}