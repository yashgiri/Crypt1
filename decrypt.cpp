//
// Created by yash on 9/21/19.
//
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


unsigned int rotatel(unsigned int input)
{
    return (input << 1)|(input >> (INT_BITS - 1));
}

std::vector<unsigned int> decryption(std::vector<unsigned int> input, unsigned int key)
{
    std::vector<unsigned int> result, output_stg2, output_stg3;
    unsigned int temp;

    cout<<"\nThe encrypted data is as follows\n";
    for(int i=0; i<input.size(); i++)
    {
        cout<<input[i];
        cout<<"\n";
        cout<<std::bitset<32>(input[i]);
        cout<<"\n";
    }

    cout<<"After P-Box reversal\n";
    //rotate left by 1 to get output_stg3
    for(int i=0; i<input.size(); i++)
    {
        output_stg3.push_back(rotatel(input[i]));
        cout<<output_stg3[i];
        cout<<"\n";
        cout<<std::bitset<32>(output_stg3[i]);
        cout<<"\n";
    }

    cout<<"After S-Box reversal\n";
    for(int i=0; i<output_stg3.size(); i++)
    {
        output_stg2.push_back(output_stg3[i]-1);
        cout<<output_stg2[i];
        cout<<"\n";
        cout<<std::bitset<32>(output_stg2[i]);
        cout<<"\n";
    }

    cout<<"The decrypted values with key "<<key<<" are\n";
    for(int i=0; i<output_stg2.size(); i++)
    {
        result.push_back(output_stg2[i] ^ key);
        cout<<result[i];
        cout<<"\n";
        cout<<std::bitset<32>(result[i]);
        cout<<"\n";
    }

    return output_stg3;
}

// Use key : feeffa

int main(int argc, char **argv)
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
    cout<<"The key in hex is : "<<key;
    input = getInput(inFileString);
	data = decryption(input, key);
	pushOutput(data, outFileString);

    return 0;
}

