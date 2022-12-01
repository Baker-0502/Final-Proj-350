all: Baker_Daniel_QuickSort.cpp InputFileGenerator.cpp
	g++ -o QuickSort Baker_Daniel_QuickSort.cpp
	g++ -o InputFileGenerator InputFileGenerator.cpp