#include "protocol.h"
#include "node.h"
#include "algorithms.h"
#include <string.h>
#include <arpa/inet.h>
int cmd_data(char *packet, char *buffer, int dsize)
{
    memcpy(protocol_response, "Data Received!", 14);
    return 14;
}

int protocol_process(char *packet, char *buffer)
{

    char cmd[6];
    char address[15];
    char destination[15];
    memcpy(cmd, packet + 15, 6);
    memcpy(address, packet, 15);
    memcpy(buffer, packet + 21, 200);

    if (memcmp(address, n_i.address, 15) == 0)
    {
        if (memcmp("DATA", cmd, 4) == 0)
        {
            debug_write(buffer);
            return cmd_data(packet, buffer, 200);
        }
        if (memcmp("MESREQ", cmd, 6) == 0)
        {
            
        }
    }
    else
    {
        debug_write("data to ");
        debug_write(address);
        uint32_t nh;
        get_next_hop(inet_addr(address), &nh);
        communication_channel_send(packet, 1024, nh, buffer, 1024);
        memcpy(protocol_response, buffer, 1024);
        //protocol_reset();
        return 0;
    }

    memcpy(protocol_response, "BAD Packet!", 11);
    return 1;
}

void protocol_reset()
{
    memset(protocol_packet, 0, 1024);
    memset(protocol_buffer, 0, 1024);
    memset(protocol_response, 0, 1024);
}