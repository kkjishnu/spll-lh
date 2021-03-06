#include <stdint.h>
#define DATA_RESPONSE "Thanks for connection!"
#define ROUTING_TABLE_UPDATE_RESPONSE "Routing Table Updated!"
#define SET_ROUTING_TABLE_RESPONSE "No Routing Table Set!"
#define MESSAGE_BAD_REQUEST "BAD REQUEST!"
// PROTOCOL MAP STARTS//
#define DATA A
#define ROUTING_TABLE_RECEIVE B
// PROTOCOL MAP ENDS //

char protocol_packet[1024];
char protocol_buffer[1024];
char protocol_response[1024];
char protocol_data[1012];
void protocol_reset();
int protocol_process(char *packet,char *buffer);
extern uint16_t protocol_response_length;
