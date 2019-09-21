#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cctype>
#include <string.h>
#include <iomanip>
#include <vector>
#include <bitset>
using namespace std;

unsigned int rotater(unsigned  int input)
{
	unsigned int temp = input & 1;
	input = input >> 1;
	input |= (temp<<31);
	return input;
}

std::vector<unsigned int> encryption(std::vector<unsigned int> input, unsigned int key)
{
	std::vector<unsigned int> input_stg1, input_stg2, input_stg3;
	unsigned int temp;
	//XOR key and 32-bit chunks of input

	for(int i=0; i<input.size(); i++)
	{
		input_stg1.push_back(key ^ input[i]);
		cout<<input_stg1[i];
		cout<<"\n";
		cout<<std::bitset<32>(input_stg1[i]);
		cout<<"\n";
	}

	cout<<"\nStarting S-box implementation\n";
	//Simple S-box implementation
	for(int i=0; i<input_stg1.size(); i++)
	{
		input_stg2.push_back(input_stg1[i]+1);
		cout<<input_stg2[i];
		cout<<"\n";
		cout<<std::bitset<32>(input_stg2[i]);
		cout<<"\n";
	}

	cout<<"\nStarting P-box implementation\n";
	//Simple P-box implementation
	for(int i=0; i<input_stg2.size(); i++)
	{
		input_stg3.push_back(rotater(input_stg2[i]));
		cout<<input_stg3[i];
		cout<<"\n";
		cout<<std::bitset<32>(input_stg3[i]);
		cout<<"\n";
	}

	return input_stg3;
}

int main()
{
	std::vector<unsigned int> input;
	unsigned int key;
	cin>>hex>>key;
	input = {11324,41323,0,131245159};
	encryption(input, key);
	return 0;
}