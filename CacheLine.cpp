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

        if (dirty)// if it is dirty you should write it right away in memory then get the
            {  // tag you want into cache
                mem_writes = mem_writes +1;
                tag = Tag;
                dirty = false; // after we write cache into mem the cache is not dirty anymore
            }
        else
            {
                tag = Tag; // in case it is not dirty just get the new tag in index

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
   if (mode =='R') // if our mode is read we only need to check the validity bit and tag then if they are true read
    {              // and increase the its if we want to read and there is no tag in cache the it is a miss and 
                   // we read the tag from the memory then get the tag through handle miss
                   // finally we read the tag after it came to cache after handle miss
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
    else// if the mode is write and validity is on it is a hot and we write then if depending on cache write policy we
    {   // either write in memory or wait for a miss and set the dirty bit to zero
        if ((tag == Tag)&& v)
            {
                hits = hits +1;
                cache_writes = cache_writes +1;

                if (wb)
                {
                    dirty = true;

                }
                else 
                {
                    mem_writes = mem_writes +1;
                }
                
            }
        else // if we want to attempt to write and the tag is not there then it is a miss we read the tag from memory
            { // then by handle miss we get the tag after that we write to the tag after is finally in cache after handle miss
                misses = misses +1;
                mem_reads = mem_reads +1;
                v = true ;
                handle_miss(Tag);
                cache_writes = cache_writes +1;
                if (wb) // after you get the tag into cache you write it, depending on your policy you then either set dirty bit or just write to memory
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