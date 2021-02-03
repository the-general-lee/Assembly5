#include "DirectMap.h"
#include "Utils.h"


DirectMap::DirectMap (uint16_t p_cache_line_size , uint16_t p_cache_size, bool _wb)
{
    cache_line_size = p_cache_line_size;
    cache_size = p_cache_size;
    cs_bits = Utils::get_first_one_pos(cache_size)-1;
    ls_bits = Utils::get_first_one_pos(cache_line_size)-1;


    for (int i =0 ; i< cache_size; i++)
    {
        CacheLine * line = new CacheLine(_wb);
        cache.insert({ i, line }) ;
    }
    

    //Write your code here
}
void DirectMap::access (uint64_t full_address,char mode)
{
    int Index = Utils::extract_bits(full_address, cs_bits, ls_bits ) ;
    int Tag_size = Utils::get_first_one_pos(full_address)- cs_bits- ls_bits -1;
    int Tag = Utils::extract_bits(full_address, Tag_size ,ls_bits+cs_bits ) ;
    cache[Index]->access(Tag, mode);
    
    
    //Write your code here, here i will have to compare the full address
    // entered to those already avaiable in the direct map at specfied
    // locations
}
void DirectMap::printStats (unsigned int crc,unsigned int cwc ,unsigned int mrc ,unsigned int mwc)
{
    // crc cache read cycles, cwc cache write cycles, memory read and write cycles
    // here we want to print all the outputs
    int TotalMisses = 0, TotalHits = 0, MemoryReadAttempts = 0, MemoryWriteAttempts = 0, MemoryAccessAttempts = 0;
    int MemoryReadAccess = 0, MemoryWriteAccess = 0, TotalCyclesCr = 0, TotalCyclesCw = 0, TotalCyclesCa = 0;
    int TotalCyclesMr = 0, TotalCyclesMw = 0, TotalCyclesMa = 0;
    for (int i = 0; i< cache_size;i++ )
    {
        TotalMisses = TotalMisses + cache[i]->getMisses();
        TotalHits = TotalHits + cache[i]->getHits();
        MemoryReadAttempts = MemoryReadAttempts + cache[i]->getCacheReads();
        MemoryWriteAttempts = MemoryWriteAttempts + cache[i]->getCacheWrites();
        MemoryReadAccess = MemoryReadAccess + cache[i]->getMEMReads();
        MemoryWriteAccess = MemoryWriteAccess + cache[i]->getMEMWrites();
    }
    MemoryAccessAttempts = MemoryReadAttempts + MemoryWriteAttempts;
    TotalCyclesCr = crc * MemoryReadAttempts;
    TotalCyclesCw = cwc * MemoryWriteAttempts;
    TotalCyclesCa = TotalCyclesCr + TotalCyclesCw;
    TotalCyclesMr = mrc * MemoryReadAccess;
    TotalCyclesMw = mwc * MemoryWriteAccess;
    TotalCyclesMa = TotalCyclesMr + TotalCyclesMw;


    std::cout<< "this is total misses:  "<<TotalMisses<<std::endl;
    std::cout<< "this is total Hits  :  "<< TotalHits<<std::endl;
    std::cout<< "this is total Memory Read Attempts    :  "<< MemoryReadAttempts<<std::endl;
    std::cout<< "this is total Memory Write Attempts   :  "<< MemoryWriteAttempts<<std::endl;
    std::cout<< "this is total Memorry Attmepts        :  "<< MemoryAccessAttempts<<std::endl;//
    std::cout<< "this is total Memory Read Access      :  "<< MemoryReadAccess<<std::endl;
    std::cout<< "this is total Memorry Write Access    :  "<< MemoryWriteAccess<<std::endl;
    std::cout<< "this is total cycles for cache reads  :  "<< TotalCyclesCr<<std::endl;//
    std::cout<< "this is total cycles for cache writes :  "<< TotalCyclesCw<<std::endl;//
    std::cout<< "this is total cycles for cache access :  "<< TotalCyclesCa<<std::endl;//
    std::cout<< "this is total cycles for memory read  :  "<< TotalCyclesMr<<std::endl;//
    std::cout<< "this is total cycles for memory writes:  "<< TotalCyclesMw<<std::endl;//
    std::cout<< "this is total cycles for memory access:  "<< TotalCyclesMa<<std::endl;//
    

    
   //Write your code here
}

DirectMap::~DirectMap()
{
    for ( uint16_t i = 0 ; i < cache_size ; i++)
        delete (cache[i]);
}
