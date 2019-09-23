//
// Created by yash on 9/21/19. Changed later.
//
#include <string>
#include <climits>
#include <vector>
#include <iostream>
#include <bitset>
#include <cctype>
#include <cstring>
#define INT_BITS 32

using namespace std;

unsigned int rotater(unsigned int input)
{
    return (input >> 1) | (input << (INT_BITS - 1));
}

unsigned int rotatel(unsigned int input)
{
    return (input << 1)|(input >> (INT_BITS - 1));
}

std::vector<unsigned int> encryption(std::vector<unsigned int> input, unsigned int key)
{
    std::vector<unsigned int> input_stg1, input_stg2, input_stg3;
    //XOR key and 32-bit chunks of input

    for (int i = 0; i < input.size(); i++)
    {
        input_stg1.push_back(key ^ input[i]);
        input_stg2.push_back(input_stg1[i] + 1);
        input_stg3.push_back(rotater(input_stg2[i]));
    }

    return input_stg3;
}

std::vector<unsigned int> decryption(std::vector<unsigned int> input, unsigned int key)
{
    std::vector<unsigned int> result, output_stg2, output_stg3;

    //rotate left by 1 to get output_stg3
    for(int i=0; i<input.size(); i++)
    {
        output_stg3.push_back(rotatel(input[i]));
        output_stg2.push_back(output_stg3[i]-1);
        result.push_back(output_stg2[i] ^ key);
    }
    return result;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "ERROR: Not enough parameters (need at least 1)" << endl;
        exit(1); // terminate with error
    }

    unsigned int key;
    char* keyString = argv[1];
    std::vector<unsigned int> input, encrypt_var, output;
    for(int i=0; i<32; i++)
    {
        input.push_back(rand());
    }
    //input = {32842934, 32842934, 3284, 3123193489};
    key = (unsigned int)strtol(keyString, NULL, 16); // reads the key as a hex string
    cout<<"Key recieved for encryption : "<<key<<" with string : "<<keyString;
    encrypt_var = encryption(input, key);

    for(unsigned int i=0; i<=UINT_MAX; i++)
    {
        cout<<"\nTrying key : "<<i;
        output = decryption(encrypt_var, i);
        cout<<"\tOutput [0] : "<<output[0]<<" should be "<<input[0];
        if(output[1] == input[1])
        {
            cout<<"\n\nFound the key : "<<i<<" with hex value "<<std::hex<<i;
            break;
        }
    }

}