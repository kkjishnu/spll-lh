#include "protocol.h"
#include "node.h"
#include "algorithms.h"
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

uint32_t protocol_address = 0;
uint16_t protocol_data_length = 0;
uint8_t protocol_cmd = 0;
uint8_t routing_table_set_flag = 0;
uint16_t protocol_response_length = 0;

int protocol_process(char *packet, char *buffer)
{
    protocol_address = ((uint8_t)packet[0] << 24) | ((uint8_t)packet[1] << 16) | ((uint8_t)packet[2] << 8) | (uint8_t)packet[3];
    protocol_cmd = packet[4];
    //printf("%d",protocol_cmd);
    protocol_data_length = (packet[5] << 8) | packet[6];
    memcpy(protocol_data, packet + 7, protocol_data_length);
    //debug_write((char)protocol_cmd);

    if (protocol_address != n_i.address)
    {
        if (routing_table_set_flag == 0)
        {
            memcpy(protocol_response, SET_ROUTING_TABLE_RESPONSE, strlen(SET_ROUTING_TABLE_RESPONSE));
            protocol_response_length = strlen(SET_ROUTING_TABLE_RESPONSE);
            return 0;
        }

        uint32_t nh;
        get_next_hop(protocol_address, &nh);
        printf("sending to hop: %lu\n", nh);
        printf("%d" ,7+protocol_data_length);
        fflush(stdout);
        communication_channel_send(packet, 7 + protocol_data_length, nh, protocol_buffer, 1024);
        return 0;
    }
    switch (protocol_cmd)
    {
        uint16_t i;
    case 'A':
        if (routing_table_set_flag == 0)
        {
            memcpy(protocol_response, SET_ROUTING_TABLE_RESPONSE, strlen(SET_ROUTING_TABLE_RESPONSE));
            protocol_response_length = strlen(SET_ROUTING_TABLE_RESPONSE);
            return 0;
        }
        debug_write(protocol_data);
        memcpy(protocol_response, DATA_RESPONSE, strlen(DATA_RESPONSE));
        protocol_response_length = strlen(DATA_RESPONSE);
        break;
    case 'B':
        debug_write("Updating Routing Table!");
        uint16_t table_len = (protocol_data[0] << 8) | protocol_data[1];
        setup_routing_table(table_len);
        for (i = 0; i < table_len; i++)
        {
            uint32_t dest_ip = 0;
            uint32_t hop_ip = 0;
            dest_ip = ((uint8_t)protocol_data[(8 * i) + 2] << 24) | ((uint8_t)protocol_data[(8 * i) + 3] << 16) | ((uint8_t)protocol_data[(8 * i) + 4] << 8) | (uint8_t)protocol_data[(8 * i) + 5];
            hop_ip = ((uint8_t)protocol_data[(8 * i) + 6] << 24) | ((uint8_t)protocol_data[(8 * i) + 7] << 16) | ((uint8_t)protocol_data[(8 * i) + 8] << 8) | (uint8_t)protocol_data[(8 * i) + 9];
            routing_table[i].dest_ip = dest_ip;
            routing_table[i].next_hop_ip = hop_ip;
        }
        memcpy(protocol_response, ROUTING_TABLE_UPDATE_RESPONSE, strlen(ROUTING_TABLE_UPDATE_RESPONSE));
        protocol_response_length = strlen(ROUTING_TABLE_UPDATE_RESPONSE);

        routing_table_set_flag = 1;
        break;
    case 'C':
        if (routing_table_set_flag == 0)
        {
            memcpy(protocol_response, SET_ROUTING_TABLE_RESPONSE, strlen(SET_ROUTING_TABLE_RESPONSE));
            protocol_response_length = strlen(SET_ROUTING_TABLE_RESPONSE);
            return 0;
        }
        for (i = 0; i < number_of_rows; i++)
        {
            protocol_response[(8 * i) + 0] = (routing_table[i].dest_ip >> 24) & 0xff;
            protocol_response[(8 * i) + 1] = (routing_table[i].dest_ip >> 16) & 0xff;
            protocol_response[(8 * i) + 2] = (routing_table[i].dest_ip >> 8) & 0xff;
            protocol_response[(8 * i) + 3] = (routing_table[i].dest_ip) & 0xff;
            protocol_response[(8 * i) + 4] = (routing_table[i].next_hop_ip >> 24) & 0xff;
            protocol_response[(8 * i) + 5] = (routing_table[i].next_hop_ip >> 16) & 0xff;
            protocol_response[(8 * i) + 6] = (routing_table[i].next_hop_ip >> 8) & 0xff;
            protocol_response[(8 * i) + 7] = (routing_table[i].next_hop_ip) & 0xff;
            protocol_response_length += 8;
        }
        break;
    default:
        memcpy(protocol_response, MESSAGE_BAD_REQUEST, 12);
        protocol_response_length = strlen(MESSAGE_BAD_REQUEST);
        break;
    }
    return 0;
}

void protocol_reset()
{
    protocol_response_length = 0;
    memset(protocol_packet, 0, 1024);
    memset(protocol_buffer, 0, 1024);
    memset(protocol_response, 0, 1024);
}