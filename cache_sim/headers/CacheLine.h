#ifndef CACHELINE_H_
#define CACHELINE_H_

#include <includes.h>
#define READ_ACCESS 'R'
#define WRITE_ACCESS 'W'

class CacheLine
{

    private:
        bool wb;
        bool v;
        uint64_t tag;
        uint64_t hits;
        uint64_t misses;
        uint64_t cache_reads;
        uint64_t cache_writes;
        uint64_t mem_reads;
        uint64_t mem_writes;
        void write_through();
        void write_back();
        void handle_miss (uint64_t p_tag);
    public:
        CacheLine (bool _wb=true);
        bool valid();
        uint64_t getTag();
        uint64_t getHits();
        uint64_t getMisses();
        uint64_t getCacheReads();
        uint64_t getCacheWrites();
        uint64_t getMEMReads();
        uint64_t getMEMWrites();
        void access (uint64_t p_tag,char mode);
        ~CacheLine();
};

#endif // CACHELINE_H_