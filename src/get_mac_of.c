/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** get_mac_of.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "arpspoof.h"

static uint8_t *mem_alloc(uint8_t *data, size_t size)
{
    uint8_t *mem = malloc(size);

    memcpy(mem, data, size);
    return mem;
}

uint8_t *get_mac_of(arp_t *arp)
{
    arp_packet_t packet;
    arp_packet_t *recv_packet;
    int sock = create_socket();
    struct sockaddr_ll dest_addr = create_dest_address(sock, arp->iface);
    socklen_t addr_size = sizeof(struct sockaddr_ll);
    char buff[4096];

    init_broadcast(&packet, arp);
    if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr *) &dest_addr,
            addr_size) == -1) {
        perror("sendto");
        exit(84);
    }
    if (recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr *) &dest_addr,
            &addr_size) == -1) {
        perror("recvfrom");
        exit(84);
    }
    recv_packet = (void *) buff;
    close(sock);
    return mem_alloc(recv_packet->eth_hdr.ether_shost, ETH_ALEN);
}

