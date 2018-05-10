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
    while (1)
    {
        //communication_channel_send("Hello",5,3232246638,"a",1);
        communication_channel_read(protocol_buffer, 1024, 1, protocol_response, 0);
    }
}