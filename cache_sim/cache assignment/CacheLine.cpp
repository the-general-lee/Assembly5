#include "CacheLine.h"

CacheLine::CacheLine (bool _wb)
{
    v = false;
    dirty = false; 
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
    int Tag = p_tag;
    if (wb)// if we write back we want to memory write only when we are changing the 
    {       // the tag

        if (dirty)// if it is dirty you should write it write away in memory then get the
            {  // tag you want into cache
                mem_writes = mem_writes +1;
                tag = Tag;
                dirty = false; // after we write cache into mem the cache is not dirty anymore
            }
        else
            {
                tag = Tag;

            }

    }
    else// if we write through we will write back to memory each time we write to cache
    {   // so we only need to get the tag into cache without writing to memory
        // because we already write to memory with every successful write to cache
        tag = Tag;

    }

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
{   // read or write
    // cycles
   //Write your code here
   int Tag = p_tag; 
   if (mode =='R')
    {
        if ((tag == Tag)&& v)
            {
                hits = hits + 1;
                cache_reads = cache_reads +1;
                // Read Hit
                
            }
        else
            {
                misses = misses + 1;
                mem_reads = mem_reads +1;
                v = true ;
                                        // shoulf i update the v here??
                                        // should i remove the handle_miss
                                        // and equate the two tags myself??
                handle_miss(Tag);
                cache_reads = cache_reads +1; 

                // Read miss but the function handle miss in cache is private
            }
    }
    else
    {
        if ((tag == Tag)&& v)
            {
                hits = hits +1;
                cache_writes = cache_writes +1;

                if (wb)
                {
                    dirty = true; // if we write we should mark this to be dirty
                         // but i don't know if we should use validity bit for that

                }
                else 
                {
                    mem_writes = mem_writes +1;
                }
                // write Hit
                
            }
        else
            {
                misses = misses +1;
                mem_reads = mem_reads +1;
                v = true ;
                handle_miss(Tag);
                cache_writes = cache_writes +1;
                if (wb)
                {
                    dirty = true; // if we write we should mark this to be dirty
                         // but i don't know if we should use validity bit for that

                }
                else 
                {
                    mem_writes = mem_writes +1;
                }

                // write miss but the function handle miss in cache is private
            }
    }
}
CacheLine::~CacheLine()
{

}