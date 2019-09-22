/*
 Created by Spencer Bouck on 9/21/2019
*/

#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <bitset>
#include "fileInteraction.h"
using namespace std;

bool debug = false;

// retrieves the input data to a given vector
vector<dataPacket> getInput(char* inFileString)
{
	vector<dataPacket> data = vector<dataPacket>();
	ifstream inFile;

	// opens an input file
	inFile.open(inFileString, ifstream::binary);
	if (!inFile) {
		cout << "Unable to open input file at " << inFileString << endl;
		exit(1); // terminate with error
	}

	// get length of file
	inFile.seekg(0, inFile.end);
	int length = inFile.tellg();
	inFile.seekg(0, inFile.beg);

	// allocate memory
	char buffer[4];

	for (int i = 0; i < length / 4; ++i)
	{
		// read data as a block
		inFile.read(buffer, 4);

		//condenses 4 8-bit chunks into a single 32-bit chunk
		dataPacket chunk = 0;
		for (int j = 0; j < 4; ++j)
		{
			if (debug)
				cout << "Reading: " << buffer[j] << " or " << (unsigned int)buffer[j] << " or " << bitset<8>((unsigned int)buffer[j]) << endl;
			chunk = chunk << 8;
			chunk += (buffer[j] & 255);
		}
		if (debug)
			cout << "Read \"" << chunk << "\" or \"" << bitset<32>(chunk) << "\" or \"" << buffer[0] << buffer[1] << buffer[2] << buffer[3] << "\" or \"" << bitset<8>(buffer[0]) << bitset<8>(buffer[1]) << bitset<8>(buffer[2]) << bitset<8>(buffer[3]) << "\" from file" << endl;
		data.push_back(chunk);
	}

	int extraChars = length % 4;
	// pads the last remaining output chunk with 0s
	if (extraChars > 0)
	{
		// reads the rest of the characters
		inFile.read(buffer, extraChars);
		// compiles last characters into a single chunk
		dataPacket finalChunk = 0;
		for (int i = 0; i < 4; ++i)
		{
			// pads the last remaining output chunk with 0s
			finalChunk = finalChunk << 8;
			if (i < extraChars)
			{
				finalChunk += buffer[i] & 255;
			}
		}
		if (debug)
			cout << "Reading \"" << finalChunk << "\" from file" << endl;
		data.push_back(finalChunk);
	}

	inFile.close(); // closes the file

	return data;
}

// pushes the given data to the file of the filename given
void pushOutput(vector<dataPacket>& data, char* outFileString)
{
	ofstream outFile;

	//cout << "Writing to: " << outFileString << endl;
	// opens a file to write to
	outFile.open(outFileString, ofstream::binary);
	if (!outFile) {
		cout << "Unable to open output file at " << outFileString << endl;
		exit(1); // terminate with error
	}

	unsigned int buffer;

	// writes to the file, iterating over all data
	for (auto iter = data.begin(); iter != data.end(); ++iter)
	{
		dataPacket chunk = *iter;

		if (debug)
			cout << "Writing chunk with value: " << chunk << " Or: " << bitset<32>(chunk) << ", Or:" << endl;
		for (int j = 0; j < 4; ++j)
		{
			buffer = ((chunk & 4278190080) >> 24);
			chunk = chunk << 8;

			// if this isn't a pad byte
			if (iter + 1 != data.end() || buffer != 0)
			{
				if (debug)
					cout << "Writing \"" << (char)buffer << "\" (or \"" << (unsigned int)buffer << "\", or \""
					<< bitset<8>(buffer)
					<<"\") to file" << endl;
				outFile << (char) buffer;
			}
		}
	}

	outFile.close(); // closes the file
}