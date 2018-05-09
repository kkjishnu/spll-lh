char protocol_packet[1024];
char protocol_buffer[1024];
char protocol_response[1024];

void protocol_reset();
int protocol_process(char *packet,char *buffer);