#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>

#define debug 1

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wconversion"
using namespace std;

typedef unsigned char byte;

class BinaryNumber {
private:
    size_t size;
    byte* stream;
    string divideBy2(string x)
    {
        int c = 0;
        for(int i =0; i<x.length(); i++)
        {
            int cur = x.at(i) - '0';
            int q = (c * 10 + cur) / 2;

            x[i] = q + '0';
            c = cur % 2;

        }

        if(x[0] == '0')
        {
            int i =0;
            while(x[i++] == '0');
            x.erase(0, i-1);
        }
        return x;
    }

    void parse(string x)
    {
        byte* ptrIt = stream;
        int ct = 0; byte partial = 0;

        while(x.length() > 0)
        {
            partial = (((x.at(x.length() - 1) - '0') % 2) << (ct++)) | partial;
            x = divideBy2(x);
            if(ct == 8)
            {
                ct = 0;
                *ptrIt = partial;
                ptrIt++;
            }
        }
        if(ct > 0)
            *ptrIt = partial;

        //reverse bytes:
        byte* secondIt = stream;
        ptrIt = stream + (size / 8) - 1;
        while(ptrIt > secondIt)
        {
            byte aux = *ptrIt;
            *ptrIt = *secondIt;
            *secondIt = aux;
            secondIt++;
            ptrIt--;
        }

        ptrIt = stream;
        while(ptrIt < stream + size/8)
        {
            cout<<(int)*ptrIt++<<endl;
        }
    }
public:
    BinaryNumber(string x)
    {
        int requiredBits = floor(log2(pow(10, x.size()))) + 1;

        requiredBits = ceil(requiredBits / (8 * 1.0)) * 8;
        if(debug)
            cout<<"Required Bits: "<<requiredBits<<endl;
        this->size = requiredBits;
        this->stream = (byte*)malloc((requiredBits / 8));

        parse(x);
    }

};


int main()
{
    BinaryNumber x("8");
    cout<<x.get();
    return 0;
}