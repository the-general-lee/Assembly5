#include <CacheLine.h>

CacheLine::CacheLine (bool _wb)
{
    v = false;
    tag =0;
    hits = 0;
    misses = 0;
    cache_reads = 0;
    cache_writes = 0;
    mem_reads = 0;
    mem_writes = 0;
    wb = _wb;
}
void CacheLine::handle_miss (uint64_t p_tag)
{
    //Write your code here
}

bool CacheLine::valid()
{
    return v;
}
uint64_t CacheLine::getTag()
{
    return tag;
}
uint64_t CacheLine::getHits()
{
    return hits;
}
uint64_t CacheLine::getMisses()
{
    return misses;
}
uint64_t CacheLine::getCacheReads()
{
    return cache_reads;
}
uint64_t CacheLine::getCacheWrites()
{
    return cache_writes;
}
uint64_t CacheLine::getMEMReads()
{
    return mem_reads;
}
uint64_t CacheLine::getMEMWrites()
{
    return mem_writes;
}
void CacheLine::access (uint64_t p_tag,char mode)
{
   //Write your code here
}
CacheLine::~CacheLine()
{

}