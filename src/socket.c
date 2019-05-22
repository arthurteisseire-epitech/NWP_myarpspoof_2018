/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** socket.c
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/if_ether.h>

int create_socket(void)
{
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

    if (sock == -1) {
        perror("socket");
        exit(84);
    }
    return sock;
}
