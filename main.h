#ifdef DEBUG
    #ifdef PRINT
        #define debug_write(x) write(1,x,strlen(x))
    #endif
#endif
#define debug_write(x) write(1,x,strlen(x));write(1,"\n",1);