#ifndef _DEBUG_H
#define _DEBUG_H

#define ERROR(format,...) fprintf(stderr,"ERROR in " __FILE__ ": " format "\n" __VA_OPT__(__VA_ARGS__))
#define FATAL(format,...) fprintf(stderr,"FATAL ERROR in " __FILE__ ": " format "\n" __VA_OPT__(__VA_ARGS__))
#define DEBUG(format,...) fprintf(stderr,__FILE__ ": " format "\n" __VA_OPT__(__VA_ARGS__))

#endif
