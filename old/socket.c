#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "nodes.h"

struct thread_data
{
    int clientfd;
    unsigned int battery_percentage;
    unsigned int distance_from_bs_x;
    unsigned int distance_from_bs_y;
    unsigned int distance_from_bs_z;
    unsigned int port;
};
void *serve_client(void *data_)
{
    struct thread_data *data;
    data = (struct thread_data *)data_;
    int client_fd = data->clientfd;

    char payload[40];
    char buffer[1024];
    memset(payload, 0, 40);
    memset(buffer, 0, 1024);

    char temp[1024];
    memset(temp, 0, 1024);

    read(client_fd, buffer, 1024);
    char cmd[5];
    char sender_data[1014];
    char sender_ip[5];
    memset(cmd, 0, 5);
    memset(sender_ip, 0, 5);
    memset(sender_data, 0, 1014);

    memcpy(cmd, buffer, 5);
    memcpy(sender_ip, buffer + 5, 5);
    memcpy(sender_data, buffer + 10, 1014);

    if (memcmp(cmd, "NDSCR", 5) == 0)
    {
        snprintf(temp, 1024, "\nGOT_DISCOVERY_REQUEST\nPORT: %d", data->port);
        write(1, temp, 1024);
        snprintf(payload, 40, "available:%s:%u:%u:%u:%u", buffer, data->battery_percentage, data->distance_from_bs_x, data->distance_from_bs_y, data->distance_from_bs_z);
        send(client_fd, payload, 40, 0);
        int ret;
        pthread_exit(&ret);
    }
    if (memcmp(cmd, "CRXTX", 5) == 0)
    {
        snprintf(temp, 1024, "\nDATA_RECEIVED\nFROM PORT: %s\nDATA: %s", sender_ip,sender_data);
        write(1, temp, 1024);
    }
}

int sock_server(int port, char *buffer, unsigned int bp, unsigned int dbsx, unsigned int dbsy, unsigned int dbsz)
{
    struct sockaddr_in address;
    struct thread_data data;
    int sockfd, clientfd, opt = 1, addrlen = sizeof(address), valread;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket creation failed. Exiting!");
        exit(EXIT_FAILURE);
    }

    if (setsockopt((int)sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Failed at setting options. Exiting!");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((uint16_t)port);

    if (bind((int)sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Binding failed. Exiting!");
        exit(EXIT_FAILURE);
    }
    if (listen((int)sockfd, 3) < 0)
    {
        perror("Failed at listening. Exiting!");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        if ((clientfd = accept((int)sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Cannot accept connection. Exiting!");
            exit(EXIT_FAILURE);
        }
        /*if (log_(port, "received request"))
        {
            perror("NON fatal error - cannot log!");
        }*/
        data.clientfd = clientfd;
        data.battery_percentage = bp;
        data.distance_from_bs_x = dbsx;
        data.distance_from_bs_y = dbsy;
        data.distance_from_bs_z = dbsz;
        data.port = port;
        pthread_t tid;
        pthread_create(&tid, NULL, serve_client, &data);
        pthread_join(tid);
        pthread_detach(tid);
    }
    return 1;
}