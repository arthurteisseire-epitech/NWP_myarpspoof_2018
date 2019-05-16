/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** utilities.c
*/

#include <stdint.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void resolve_addr(struct ifconf *ifc, int sock, struct ifreq *ifr,
    int *success)
{
    struct ifreq *it = (*ifc).ifc_req;
    const struct ifreq *const end =
        it + ((*ifc).ifc_len / sizeof(struct ifreq));

    for (; it != end; ++it) {
        strcpy((*ifr).ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, ifr) == -1)
            continue;
        if (!((*ifr).ifr_flags & IFF_LOOPBACK)) {
            if (ioctl(sock, SIOCGIFHWADDR, ifr) == 0) {
                (*success) = 1;
                break;
            }
        }
    }
}

uint8_t *get_mac_addr(void)
{
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[1024];
    int success = 0;
    unsigned char *mac_address = malloc(6);
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    if (sock == -1)
        exit(84);
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1)
        exit(84);
    resolve_addr(&ifc, sock, &ifr, &success);
    if (success)
        memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
    close(sock);
    return mac_address;
}

char *char6_to_mac(const unsigned char *mac_addr)
{
    char *macStr = malloc(18);

    snprintf(macStr, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4],
            mac_addr[5]);
    printf("mac_addr : %s\n", macStr);
    return macStr;
}