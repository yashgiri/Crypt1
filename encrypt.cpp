#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cctype>
#include <string.h>
#include <iomanip>
#include <vector>
#include <bitset>
#include "fileInteraction.cpp"
#define INT_BITS 32
using namespace std;

unsigned int rotater(unsigned int input)
{
	//cout << "Rotating " << std::bitset<32>(input) << " to " << std::bitset<32>((input >> 1) | (input << (INT_BITS - 1)));
	//cout << "First Term: " << std::bitset<32>(input >> 1) << " Second Term: " << std::bitset<32>(input << (INT_BITS - 1)) << endl;
	return (input >> 1) | (input << (INT_BITS - 1));
}

std::vector<unsigned int> encryption(std::vector<unsigned int> input, unsigned int key)
{
	std::vector<unsigned int> input_stg1, input_stg2, input_stg3;
	unsigned int temp;
	//XOR key and 32-bit chunks of input

	for (int i = 0; i < input.size(); i++)
	{
		input_stg1.push_back(key ^ input[i]);
		cout << input_stg1[i];
		cout << "\n";
		cout << std::bitset<32>(input_stg1[i]);
		cout << "\n";
	}

	cout << "\nStarting S-box implementation\n";
	//Simple S-box implementation
	for (int i = 0; i < input_stg1.size(); i++)
	{
		input_stg2.push_back(input_stg1[i] + 1);
		cout << input_stg2[i];
		cout << "\n";
		cout << std::bitset<32>(input_stg2[i]);
		cout << "\n";
	}

	cout<<"\nStarting P-box implementation\n";
	//Simple P-box implementation
	for (int i = 0; i < input_stg2.size(); i++)
	{
		input_stg3.push_back(rotater(input_stg2[i]));
		cout << input_stg3[i];
		cout << "\n";
		cout << std::bitset<32>(input_stg3[i]);
		cout << "\n";
	}

	return input_stg3;
}

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cout << "ERROR: Not enough parameters (need at least 3)" << endl;
		exit(1); // terminate with error
	}

	// initialize values, assign key values
	unsigned int key;

	char* keyString = argv[1];
	char* inFileString = argv[2];
	char* outFileString = argv[3];

	std::vector<unsigned int> input;
	vector<unsigned int> data;

	key = (unsigned int)strtol(keyString, NULL, 16); // reads the key as a hex string
	cout << "The key in hex is : " << key << endl;
	input = getInput(inFileString);
	data = encryption(input, key);
	pushOutput(data, outFileString);
	/*
	vector<unsigned int> testVector1 = { 1, 2, 3, 2147483649, 3333333332, 850999078, 1282372197 };
	vector<unsigned int> testVector2 = encryption(testVector1, 0);
	cout << "\nTEST Encryption: [";
	for (int i = 0; i < testVector2.size(); ++i)
	{
		cout << testVector2[i] << ", ";
	}
	cout << "]" << endl;
	*/
	return 0;
}