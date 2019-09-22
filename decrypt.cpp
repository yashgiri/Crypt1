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

int main()
{
    std::vector<unsigned int> input;
    unsigned int key;
    cout<<"Enter decryption key : ";
    cin>>hex>>key;
    input = {2155831779,8333129,2155837437,60171727};
    decryption(input, key);
    return 0;
}

