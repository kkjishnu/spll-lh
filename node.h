#include "main.h"
#include <stdint.h>

struct node_information {
    char address[15];
    uint8_t battery_percentage;
    uint32_t position_x;
    uint32_t position_y;
    uint32_t position_z;
    uint32_t unique_number;
} n_i;

struct routing_table_row {
    uint32_t sequence_number;
    uint32_t src_ip;
    uint16_t src_port;
    uint32_t dest_ip;
    uint16_t dest_port;
    uint32_t next_hop_ip;
    uint16_t next_hop_port;
};

uint16_t number_of_rows;
struct routing_table_row *routing_table;

int communication_channel_send(char *payload, int psize, uint32_t address,char *buffer,int bsize);
int communication_channel_read(char *buffer,int bsize,int msg_, char *msg,int forever);
int get_battery();
void get_position(uint16_t *position);
int initialize_node_information(struct node_information *n_i);
int check_for_routing_table();
void setup_routing_table(uint16_t nsize);
int init(char *address,char *port);