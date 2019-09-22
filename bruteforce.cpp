//
// Created by yash on 9/21/19.
//

#include <climits>
#include <vector>
#include <iostream>
#include <bitset>
#include <cctype>
#define INT_BITS 32

using namespace std;

// the key that will give result is feeffa

unsigned int rotatel(unsigned int input)
{
    return (input << 1)|(input >> (INT_BITS - 1));
}

std::vector<unsigned int> decryption(std::vector<unsigned int> input, unsigned int key)
{
    std::vector<unsigned int> result, output_stg2, output_stg3;
    unsigned int temp;

    //rotate left by 1 to get output_stg3
    for(int i=0; i<input.size(); i++)
    {
        output_stg3.push_back(rotatel(input[i]));
        output_stg2.push_back(output_stg3[i]-1);
        result.push_back(output_stg2[i] ^ key);
    }
    return output_stg3;
}

int main()
{
    std::vector<unsigned int> input, output;
    input = {2155831779};
    for(unsigned int i=0; i<=UINT_MAX; i++)
    {
        cout<<"\nTrying key : "<<i;
        output = decryption(input, i);
        if(output[0] == 2155831779)
        {
            cout<<"\nFound key with value : "<<i;
            break;
        }
    }

}