/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** print.c
*/

#include <stdio.h>
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
    print_packet((unsigned char *) &packet, sizeof(packet));
    return 0;
}

int print_broadcast(arp_t *arp)
{
    arp_packet_t packet;

    init_broadcast(&packet, arp->dest_ip);
    print_packet((unsigned char *) &packet, sizeof(packet));
    return 0;
}
