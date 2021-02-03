#ifndef UTILS_H_
#define UTILS_H_

#include "includes.h"

class Utils{
    public:
        template <typename T>
        static uint8_t count_bits (T n) { // simply tells us if the number is power of 2
            int counter = 0;              // or not does not do any counting 
            while(n) {
                counter += n % 2;
                n >>= 1;
            }
            return counter;
        }
        
        template <typename T>
        static uint8_t get_first_one_pos (T n) {    // tells us the size of bitwise
            uint8_t position = 1;                   // given this bitwise is divisible 
            T m = 1;                                // by 2
            while (!(n & m)) {
                m = m << 1;
                position++;
            }
            return position;
        }

        template <typename T>
        static T extract_bits(T n , int count, int from) // the n is the number we want 
        {                                               // we want to extract bits from
            T x = 1;                                   // count is how many digits to 
            x <<= count;                              // extract, from is from which
            x -=1;                                   // digit from the right
            T y = n >> (from);
            return (x&y);
        }
};



#endif