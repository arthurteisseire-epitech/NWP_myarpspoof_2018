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
#include "arpspoof.h"

int print_spoofed(arp_t *arp)
{
    (void)arp;
    return 0;
}

int print_broadcast(arp_t *arp)
{
    struct ether_arp hdr;
    init_ethernet_frame(&hdr);

    char *hdr_as_byte_array = (char *)&hdr;

    for (int i = 0; i < sizeof(hdr); ++i) {
        char byte = hdr_as_byte_array[i];
        printf("%02x ", byte);
        printf("%d ", byte);
    }
    printf("%ld\n", sizeof(hdr));
    printf("%s\n", "bite");
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