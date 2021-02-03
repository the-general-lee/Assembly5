#include <Dispatcher.h>

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
        int r = fscanf(f, "%s %c %llx\n", skip, &mode,&address);
        while (r != EOF)
        {
            //Write your code here
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
