#include <stdio.h>
#include <stdint.h>

unsigned int get_random()
{
    unsigned int ret;
    FILE *f;
    f = fopen("/dev/urandom", "r");
    fread(&ret, 1, 1, f);
    fclose(f);
    return ret;
}

unsigned int get_random_l()
{
    unsigned int ret;
    FILE *f;
    f = fopen("/dev/urandom", "r");
    fread(&ret, 4, 1, f);
    fclose(f);
    return ret;
}

int log_(int port, char *s)
{
    FILE *f;
    f = fopen("log_file.log", "a+"); 
    if (f == NULL)
    { 
        return 1;
    }
    fprintf(f, "%d: %s\n",port,s);
    fclose(f);
    return 0;
}