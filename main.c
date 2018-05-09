#define DEBUG
#include "main.h"
#include "node.h"
#include "protocol.h"
#include <stdio.h> // debug on

#include <string.h>

int main()
{
    initialize_node_information(&n_i);
    while (1)
    {
        communication_channel_read(protocol_packet, 1024, 1, protocol_response, 0);
    }
}