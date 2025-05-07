#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <algorithm>
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        const int GROUPS = 5;
        const int CHUNK = 6;

        unsigned long long w[GROUPS] = {0,0,0,0,0};
        int len = static_cast<int>(k.size());

        for(int g = 0; g < GROUPS; ++g) {
            unsigned long long accum = 0;
            int end = len - g * CHUNK;
            int start = std::max(0, end - CHUNK);
            if (end <= 0){
                break;
            }

            for(int i = start; i < end; ++i){
                accum = accum * 36ULL + letterDigitToNumber(k[i]);
            }

            w[GROUPS - 1 - g] = accum;
        }

        unsigned long long h = 0;
        for(int i = 0; i < GROUPS; ++i){
            h += static_cast<unsigned long long>(rValues[i]) * w[i];
        }
        
        return static_cast<HASH_INDEX_T>(h);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        unsigned char c = static_cast<unsigned char>(letter);

        if(isalpha(c)){
            char lower = static_cast<char>(tolower(c));
            return static_cast<HASH_INDEX_T>(lower -'a');
        }
        else if (isdigit(c)){
            return static_cast<HASH_INDEX_T>(26 + (c - '0'));
        }

        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
