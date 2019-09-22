/*
 Created by Spencer Bouck on 9/21/2019
*/

#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "fileInteraction.h"
using namespace std;

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
			chunk = chunk << 8;
			chunk += (dataPacket)buffer[j];
		}
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
				finalChunk += (dataPacket)buffer[i];
			}
		}
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

	char buffer;

	// writes to the file, iterating over all data
	for (auto iter = data.begin(); iter != data.end(); ++iter)
	{
		dataPacket chunk = *iter;
		for (int j = 0; j < 4; ++j)
		{
			buffer = chunk;
			chunk = chunk >> 8;

			// if this isn't a pad byte
			if (iter + 1 != data.end() || buffer != 0)
			{
				outFile << buffer;
			}
		}
	}

	outFile.close(); // closes the file
}