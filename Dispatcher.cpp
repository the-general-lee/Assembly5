#include "Dispatcher.h"

Dispatcher::Dispatcher(DirectMap * p_directMap,char * filename)
{
    directMap = p_directMap;
    f = fopen (filename,"r");
    if ( f == NULL )
    {
        printf ("Invalide file name: %s\n",filename);
        exit(1);
    }
}
bool Dispatcher::dispatch ()
{
    if ( f != NULL)
    {
        uint64_t address;
        char skip[100];
        char mode;
        int r = fscanf(f, "%s %c %llx\n", skip, &mode,&address); // this gets the instruction address in skip, the mode in mode and the memory address in address
        while (r != EOF)
        {
            directMap->access(address, mode); // ineed to pass this memory address and mode to the directmap and keep doing so until all lines are finished
            //Write your code here, here i will
            // have to access with the mode and address i have got
            r = fscanf(f, "%s %c %llx\n", skip, &mode,&address);
        }
        return true;
    }
    else return false;
}
Dispatcher::~Dispatcher()
{
    if ( f != NULL) fclose (f);
}
