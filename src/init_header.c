/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** init_header.c
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/if_ether.h>
#include <string.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "arpspoof.h"

static void init_arp_header(struct arphdr *hdr)
{
    hdr->ar_hln = ETHER_ADDR_LEN;
    hdr->ar_hrd = htons(ARPHRD_ETHER);
    hdr->ar_op = htons(ARPOP_REQUEST);
    hdr->ar_pln = sizeof(in_addr_t);
    hdr->ar_pro = htons(ETHERTYPE_IP);
}

void init_broadcast(arp_packet_t *packet_hdr, arp_t *arp)
{
    uint8_t *buf = get_mac_addr();
    struct in_addr s_ip;
    struct in_addr d_ip;

    memset(&packet_hdr->eth_hdr.ether_dhost, 255, 6);
    packet_hdr->eth_hdr.ether_type = 0x0608;
    memcpy(&packet_hdr->eth_hdr.ether_shost, buf, 6);
    init_arp_header(&packet_hdr->eth_arp.ea_hdr);
    memcpy(&packet_hdr->eth_arp.arp_sha, buf, 6);
    memset(&packet_hdr->eth_arp.arp_tha, 255, 6);
    if (inet_aton(arp->dest_ip, &d_ip) == -1)
        exit(84);
    if (inet_aton(arp->source_ip, &s_ip) == -1)
        exit(84);
    memcpy(&packet_hdr->eth_arp.arp_spa, &s_ip, sizeof(int));
    memcpy(&packet_hdr->eth_arp.arp_tpa, &d_ip, sizeof(int));
    free(buf);
}

void mac_to_char6(const unsigned char *s, unsigned char *to_fill)
{
    int c = 0;

    for (int i = 0; s[i]; ++i)
        if (s[i] != ':') {
            to_fill[c] = strtol((const char *) &s[i], NULL, 16);
            ++c;
            ++i;
        }
}

void init_spoofed(arp_packet_t *packet_hdr, arp_t *arp)
{
    uint8_t *buf = get_mac_addr();
    struct in_addr s_ip;
    struct in_addr d_ip;

    mac_to_char6((unsigned char *) arp->mac_address,
        (unsigned char *) &packet_hdr->eth_hdr.ether_dhost);
    packet_hdr->eth_hdr.ether_type = ETHERTYPE_ARP;
    memcpy(&packet_hdr->eth_hdr.ether_shost, buf, 6);
    init_arp_header(&packet_hdr->eth_arp.ea_hdr);
    memcpy(&packet_hdr->eth_arp.arp_sha, buf, 6);
    mac_to_char6((unsigned char *) arp->mac_address,
        (unsigned char *) &packet_hdr->eth_arp.arp_tha);
    if (inet_aton(arp->dest_ip, &d_ip) == -1)
        exit(84);
    if (inet_aton(arp->source_ip, &s_ip) == -1)
        exit(84);
    memcpy(&packet_hdr->eth_arp.arp_spa, &s_ip, sizeof(int));
    memcpy(&packet_hdr->eth_arp.arp_tpa, &d_ip, sizeof(int));
    free(buf);
}

void init_ethernet_frame(struct ether_arp *hdr)
{
    init_arp_header(&hdr->ea_hdr);
    memset(&hdr->arp_tha, 0, sizeof(hdr->arp_tha));
}
