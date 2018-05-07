#include "socket.h"
#include "stdio.h"
//#include "nodes.h"
#include <pthread.h>

void *node(void *port)
{
    int retval;
    unsigned int battery_percentage = get_random() % 100;
    unsigned int distance_from_bs_x;
    unsigned int distance_from_bs_y;
    unsigned int distance_from_bs_z;
    unsigned int unique_serial_number;

    while (1)
    {
        distance_from_bs_x = get_random_l() % 1500;
        if (distance_from_bs_x <= 1500)
        {
            break;
        }
    }
    while (1)
    {
        distance_from_bs_y = get_random() % 10;
        if (distance_from_bs_y <= 10)
        {
            break;
        }
    }
    while (1)
    {
        distance_from_bs_z = get_random_l() % 1500;
        if (distance_from_bs_z <= 1500)
        {
            break;
        }
    }

    int p = *((int *)port);
    unique_serial_number = p * 967;

    printf("node at :%d\n", p); //bp: %d\ndbs: %d\n", p,ni->battery_percentage,ni->distance_from_bs);
    char buffer[1024] = {0};
    sock_server(p, buffer, battery_percentage, distance_from_bs_x, distance_from_bs_y, distance_from_bs_z); //,ni);
    printf(buffer);
    pthread_exit(&retval);
}

void setup_nodes(int num, int *list)
{
    pthread_t tid[num];
    int i = 0, j;
    int port_list[num];
    unsigned int max_connections = num / 5;
    
    for (j = 0; j < num; j++) // port list creation
    {
        port_list[j] = 54320 + list[j];
        //printf("%d\n",54320+list[j]);
    }
    /*for (i = 0; i < num; i++) // print port list
    {
        printf("%d-", port_list[i]);
    }*/
    printf("\ncreating threads...\n");
    sleep(1);
    for (i = 0; i < num; i++)
    {
        pthread_create(&tid[i], NULL, node, (void *)&port_list[i]);
    }
    for (i = 0; i < num; i++)
    {
        pthread_join(tid[i], NULL);
    }
}