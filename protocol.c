#include "protocol.h"
#include "node.h"
#include "algorithms.h"
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

uint32_t protocol_address = 0;
uint16_t protocol_data_length = 0;
uint8_t protocol_cmd = 0 ;

int protocol_process(char *packet, char *buffer)
{
    
    protocol_address = (packet[0] << 24) | (packet[1] << 16) | (packet[2] << 8) | packet[3];
    protocol_cmd = packet[4];
    printf("%d",protocol_cmd);
    protocol_data_length = (packet[5] << 8) | packet[6];
    memcpy(protocol_data, packet + 7, protocol_data_length);
    //debug_write((char)protocol_cmd);
    switch(protocol_cmd){
        case 'A':
            debug_write(protocol_data);
            memcpy(protocol_response,DATA_RESPONSE,strlen(DATA_RESPONSE));
            break;
        case 'B':
            debug_write("Updating Routing Table!");
            memcpy(protocol_response,ROUTING_TABLE_UPDATE_RESPONSE,strlen(ROUTING_TABLE_UPDATE_RESPONSE));
            break;
        default:
            memcpy(protocol_response,"BAD REQUEST!",12);
            break;
    }
    return 0;
}

void protocol_reset()
{
    memset(protocol_packet, 0, 1024);
    memset(protocol_buffer, 0, 1024);
    memset(protocol_response, 0, 1024);
}