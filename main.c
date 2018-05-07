#define DEBUG
#include "main.h"
#include "node.h"
#include <stdio.h> // debug on

#include <string.h>

int main()
{
    char buffer[100];
    char *tmp = "tmparray!";
    initialize_node_information(&n_i);
    communication_channel_read(buffer, 100, 1, tmp, 0);
    debug_write(buffer);
}