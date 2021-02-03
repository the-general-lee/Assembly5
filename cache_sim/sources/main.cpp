#include <includes.h>
#include <CacheLine.h>
#include <DirectMap.h>
#include <Dispatcher.h>
#include <Utils.h>

void validate_inputs (unsigned int cs,unsigned int ls,char * cache_mode, unsigned int crc,unsigned int cwc ,unsigned int mrc ,unsigned int mwc)
{
        if (Utils::count_bits(cs) != 1 )
        {
                printf ("Cache size should be power of 2\n");
                exit(1);
        }
        if (Utils::count_bits(ls) != 1 )
        {
                printf ("Line size should be power of 2\n");
                exit(1);
        }

        if ( crc == 0 )
        {
                printf ("Cache Read Cycles need to be a value larger than zero\n");
                exit(1);
        }
        if ( cwc == 0 )
        {
                printf ("Cache Read Cycles need to be a value larger than zero\n");
                exit(1);
        }
        if ( mrc == 0 )
        {
                printf ("Cache Read Cycles need to be a value larger than zero\n");
                exit(1);
        }
        if ( mwc == 0 )
        {
                printf ("Cache Read Cycles need to be a value larger than zero\n");
                exit(1);
        }
        if (strcmp (cache_mode,"wb") != 0 && strcmp (cache_mode,"wt") != 0)
        {
                printf ("cache mode needs to be either wb -> write back or wt -> write through\n");
                exit(1);
        }
}


int main (int argc, char ** argv)
{
        if ( argc != 9 )
        {
                printf ("usage: %s <cache mode: wb|wt> <file_name> <cache-size> <line-size> <cache-read-cycles> <cache-write-cycles> <mem-read-cycles> <mem-write-cycles> \n",argv[0]);
                exit(1);
        }
        unsigned int cs = atoi(argv[3]);
        unsigned int ls = atoi(argv[4]);
        unsigned int crc = atoi(argv[5]);
        unsigned int cwc = atoi(argv[6]);
        unsigned int mrc = atoi(argv[7]);
        unsigned int mwc = atoi(argv[8]);


        validate_inputs (cs,ls,argv[1],crc,cwc,mrc,mwc);
        bool wb = true;
        if (strcmp (argv[1],"wt") == 0 ) wb = false;
        DirectMap directMap (ls,cs,wb);
        Dispatcher dispatcher (&directMap,argv[2]);
        dispatcher.dispatch();
        directMap.printStats(crc,cwc,mrc,mwc);
        return 0;
}
