#ifndef DIRECTMAP_H_
#define DIRECTMAP_H_

#include "includes.h"
#include "CacheLine.h"


class DirectMap
{
    private:
        uint16_t cache_line_size;
        uint16_t cache_size;
        uint8_t cs_bits;
        uint8_t ls_bits;
        std::map <uint16_t,CacheLine *> cache;
    public:
        DirectMap (uint16_t p_cache_line_size , uint16_t p_cache_size, bool _wb=true);
        void access (uint64_t full_address,char mode);
        void printStats (unsigned int crc,unsigned int cwc ,unsigned int mrc ,unsigned int mwc);
        ~DirectMap();
};




#endif // CACHELINE_H_