#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include "socket.h"
#include "essential.h"
//#include "nodes.h"
#include <string.h>

int generate_list(int *list,int num);

int main()
{
    int list[100],i;
    int num = generate_list(list,100);
    setup_nodes(num,list);
}
    
int generate_list(int *real_list,int num) 
{
    int list[100];
    int i, j, rand_num;
    memset(list, 0, num);
    list[0] = get_random() % num;
    memset(real_list, 0, num);
    int real_list_i = 0;
    for (i = 1; i < num; i++)
    {
        rand_num = get_random() % num;
        //rand_num = 2;
        int f = 0;
        while (1)
        {
            for (j = 0; j < i; j++)
            {
                if (real_list[j] == rand_num)
                {
                    f = 1;
                    //printf("matchfound");
                    rand_num = get_random() % num;
                    break;
                }
            }
            break;
        }
        if (!f)
        {
            real_list[real_list_i] = rand_num;
            real_list_i += 1;
        }
    }
    
    for (i = 0; i < real_list_i; i++)
    {
        //printf("%d-", real_list[i]);
    }
    printf("\nNodes available: %d\n", real_list_i);
    
    return real_list_i;
}
