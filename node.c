#include "main.h"
#include "node.h"
#include "protocol.h"
#include <stdint.h>
#include <stdio.h> // API specific includes
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

// APIs all the function depends on the device the code will be compiled for.

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int communication_channel_send(char *payload, int psize, uint32_t address, char *buffer, int bsize)
{
    //write(1,payload,psize);
    //protocol_reset();
    struct sockaddr_in addr;
    struct sockaddr_in server_address;
    int sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        debug_write("error opening socket...\n");
        return 1;
    }
    memset(&server_address, '0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(2500);
    
    server_address.sin_addr.s_addr = htonl(address);
    /*if (inet_pton(AF_INET, address, &server_address.sin_addr) <= 0)
    {
        debug_write("error setting server address...\n");
        return 1;
    }*/
    //printf("%lu",server_address.sin_addr.s_addr);
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        debug_write("error connecting to the server...\n");
        return 1;
    }
    send(sock, payload, psize, 0);
    read(sock, buffer, bsize);
    close(sock);
    return 0;
}
int communication_channel_read(char *buffer, int bsize, int msg_, char *msg, int forever)
{
    protocol_reset();
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        debug_write("socket failed...");
        return 1;
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        debug_write("socket option failed...");
        return 1;
    }
    //fcntl(server_fd,F_SETFL,O_NONBLOCK);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(2500);
    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        debug_write("bind failed...");
        return 1;
    }
    if (listen(server_fd, 5) < 0)
    {
        debug_write("listen failed...");
        return 1;
    }
    while (forever+1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            debug_write(strerror(errno));
            debug_write("accept failed...");
            return 1;
        }
        valread = read(new_socket, buffer, bsize);
        protocol_process(buffer,protocol_buffer);
        if (msg_)
        {
            send(new_socket, protocol_response,protocol_response_length, 0);
        }
        else
        {
            send(new_socket, "0", 1, 0);
        }
        if (forever == 0) {
            break;
        }
    }
    close(server_fd);
    close(new_socket);
    return 0;
}
int get_battery()
{
    // this code depends on the device the code will be compiled for.
    FILE *f;
    f = fopen("/dev/urandom", "r");
    uint8_t random_int;
    fread(&random_int, 1, 1, f);
    return random_int % 101;
}
void get_position(uint16_t *position)
{
    // this code depends on the device the code will be compiled for.
    FILE *f;
    f = fopen("/dev/urandom", "r");
    uint8_t position_x;
    uint8_t position_y;
    uint8_t position_z;
    fread(&position_x, 1, 1, f);
    fread(&position_y, 1, 1, f);
    fread(&position_z, 1, 1, f);
    position[0] = position_x;
    position[1] = position_y;
    position[2] = position_z;
}
// this function used the above defined funtions so this function will not depend on the device.
int initialize_node_information(struct node_information *n_i)
{
    n_i->address = 2130706433;
    n_i->battery_percentage = get_battery();
    uint16_t position[3];
    get_position(position);
    n_i->position_x = position[0];
    n_i->position_y = position[1];
    n_i->position_z = position[2];
    n_i->unique_number = 4276543210;
}
int check_for_routing_table()
{
}
void setup_routing_table(uint16_t nsize)
{
    number_of_rows = nsize;
    routing_table = malloc(nsize * (sizeof(struct routing_table_row)));
}