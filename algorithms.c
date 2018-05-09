#include "node.h"

void search_table(uint32_t what,uint8_t what_size, struct routing_table_row *routing_table, int number_of_rows)
{
    int i;
    for (i = 0; i < number_of_rows; i++)
    {
        
    }
}

void get_next_hop(uint32_t address,uint32_t *net_hop) {
    int i;
    for(i=0;i<number_of_rows;i++) {
        if (routing_table[i].dest_ip == address) {
            *net_hop = (uint32_t) routing_table[i].next_hop_ip;
        }
    }
}