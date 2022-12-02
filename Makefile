all: Baker_Daniel_QuickSort.cpp InputFileGenerator.cpp
	g++ -std=c++17 -o QuickSort Baker_Daniel_QuickSort.cpp
	g++ -std=c++17 -o InputFileGenerator InputFileGenerator.cpp