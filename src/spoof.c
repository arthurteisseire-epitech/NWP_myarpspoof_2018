/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** spoof
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/ether.h>
#include "arpspoof.h"

void print_packet(const unsigned char *packet, size_t size)
{
    printf("%02x", packet[0]);
    for (size_t i = 1; i < size; ++i)
        printf(" %02x", packet[i]);
    printf("\n");
}

int print_spoofed(arp_t *arp)
{
    arp_packet_t packet;

    init_spoofed(&packet, arp);
    print_packet((unsigned char *)&packet, sizeof(packet));
    return 0;
}

int print_broadcast(arp_t *arp)
{
    arp_packet_t packet;

    init_broadcast(&packet, arp);
    print_packet((unsigned char *)&packet, sizeof(packet));
    return 0;
}

int arp_spoof(arp_t *arp)
{
    (void)arp;
    return 0;
}

void free_arp(arp_t *arp)
{
    free(arp->dest_ip);
    free(arp->iface);
    free(arp->mac_address);
    free(arp->source_ip);
    free(arp);
}

int my_arpspoof(arp_t *arp)
{
    int n;
    struct ether_arp;

    if (arp->spoof_opt == 1)
        n = print_spoofed(arp);
    else if (arp->broadcast_opt == 1)
        n = print_broadcast(arp);
    else
        n = arp_spoof(arp);
    free_arp(arp);
    return n;
}