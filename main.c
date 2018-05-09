#define DEBUG
#include "main.h"
#include "node.h"
#include "protocol.h"
#include "algorithms.h"
#include <stdio.h> // debug on
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    initialize_node_information(&n_i);

    setup_routing_table(4);
    routing_table[0].dest_ip = 0;
    routing_table[0].next_hop_ip = 0;

    while (1)
    {
        communication_channel_read(protocol_buffer, 1024, 1, protocol_response, 0);
    }
}