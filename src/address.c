/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** header.c
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

static int find_ifindex(int sockfd, const char *if_name)
{
    struct ifreq ifr;
    size_t if_name_len = strlen(if_name);

    if (if_name_len < sizeof(ifr.ifr_name)) {
        memcpy(ifr.ifr_name, if_name, if_name_len);
        ifr.ifr_name[if_name_len] = 0;
    } else {
        fprintf(stderr, "interface name is too long");
        exit(84);
    }
    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1) {
        perror("ioctl");
        exit(84);
    }
    return ifr.ifr_ifindex;
}

struct sockaddr_ll create_dest_address(int sockfd, const char *if_name)
{
    const unsigned char ether_broadcast_addr[] =
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    struct sockaddr_ll addr = {0};

    addr.sll_family = AF_PACKET;
    addr.sll_ifindex = find_ifindex(sockfd, if_name);
    addr.sll_halen = ETHER_ADDR_LEN;
    addr.sll_protocol = htons(ETH_P_ARP);
    memcpy(addr.sll_addr, ether_broadcast_addr, ETHER_ADDR_LEN);
    return addr;
}
