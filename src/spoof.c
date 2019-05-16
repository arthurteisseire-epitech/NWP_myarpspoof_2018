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
#include <string.h>
#include <netinet/ether.h>
#include <unistd.h>
#include "arpspoof.h"

static void print_mac_address(uint8_t mac[ETH_ALEN])
{
    char *sep = "";

    for (size_t i = 0; i < ETH_ALEN; ++i) {
        printf("%s%02X", sep, mac[i]);
        sep = ":";
    }
}

static void send_packet(arp_packet_t *packet)
{
    printf("Found victim’s MAC address: '");
    print_mac_address(packet->eth_hdr.ether_dhost);
    printf("'\n");
}

int arp_spoof(arp_t *arp)
{
    arp_packet_t packet;
    uint8_t *mac = get_mac_of(arp);

    init_broadcast(&packet, arp);
    memcpy(packet.eth_hdr.ether_dhost, mac, ETH_ALEN);
    memcpy(packet.eth_arp.arp_tha, mac, ETH_ALEN);
    free(mac);
    send_packet(&packet);
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

    if (arp->spoof_opt == 1)
        n = print_spoofed(arp);
    else if (arp->broadcast_opt == 1)
        n = print_broadcast(arp);
    else
        n = arp_spoof(arp);
    free_arp(arp);
    return n;
}