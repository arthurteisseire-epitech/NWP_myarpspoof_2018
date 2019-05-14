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

void resolve_addr(struct ifconf *ifc, int sock, struct ifreq *ifr, int *success
);

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

void resolve_addr(struct ifconf *ifc, int sock, struct ifreq *ifr, int *success
)
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