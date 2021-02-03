#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <includes.h>
#include <DirectMap.h>

class Dispatcher{

    private:
        FILE * f;
        DirectMap * directMap;
    public:
        Dispatcher(DirectMap * p_directMap,char * filename);
        bool dispatch ();
        ~Dispatcher();
};

#endif
