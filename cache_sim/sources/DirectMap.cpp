#include <DirectMap.h>
#include <Utils.h>


DirectMap::DirectMap (uint16_t p_cache_line_size , uint16_t p_cache_size, bool _wb)
{
    //Write your code here
}
void DirectMap::access (uint64_t full_address,char mode)
{
    //Write your code here
}
void DirectMap::printStats (unsigned int crc,unsigned int cwc ,unsigned int mrc ,unsigned int mwc)
{
   //Write your code here
}

DirectMap::~DirectMap()
{
    for ( uint16_t i = 0 ; i < cache_size ; i++)
        delete (cache[i]);
}
