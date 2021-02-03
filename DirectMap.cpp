#include "DirectMap.h"
#include "Utils.h"


DirectMap::DirectMap (uint16_t p_cache_line_size , uint16_t p_cache_size, bool _wb)
{
    cache_line_size = p_cache_line_size; // initalize the attributes of the class
    cache_size = p_cache_size;
    cs_bits = Utils::get_first_one_pos(cache_size)-1; // get the number of bits in that number to be used later in extract bit
    ls_bits = Utils::get_first_one_pos(cache_line_size)-1; // same as above


    for (int i =0 ; i< cache_size; i++)
    {
        CacheLine * line = new CacheLine(_wb); // intialize as many cachelines as the user input dictated for the cache sizr
        cache.insert({ i, line }) ; // initialize them to the write policy that the user input specified
    }
    

    //Write your code here
}
void DirectMap::access (uint64_t full_address,char mode)
{
    int Index = Utils::extract_bits(full_address, cs_bits, ls_bits ) ; // since cs_bits represent the number of bits in index we put it at counter, then since ls_its represent the offset we start after it, to get the index
    int Tag_size = Utils::get_first_one_pos(full_address)- cs_bits- ls_bits -1; // this gives me how many bits is there for tag
    int Tag = Utils::extract_bits(full_address, Tag_size ,ls_bits+cs_bits ) ;// i put this how many here to extract the exact number, this is after an both offset and index
    cache[Index]->access(Tag, mode);// then i access the cachline with the same index as the address from the file and i pass it the tag and the mode
    
    
    //Write your code here, here i will have to compare the full address
    // entered to those already avaiable in the direct map at specfied
    // locations
}
void DirectMap::printStats (unsigned int crc,unsigned int cwc ,unsigned int mrc ,unsigned int mwc)
{
    // crc cache read cycles, cwc cache write cycles, memory read and write cycles
    // here we want to print all the outputs
    // the outputs are in order specified in assginemnt 6 pdf no need for further documentation.
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
