/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** args
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arpspoof.h"

arp_t *parse(int ac, char **av)
{
    arp_t *arp = malloc(sizeof(arp_t));

    arp->source_ip = strdup(av[1]);
    arp->dest_ip = strdup(av[2]);
    arp->iface = strdup(av[3]);
    arp->broadcast_opt = 0;
    arp->spoof_opt = 0;
    arp->mac_address = NULL;
    if (ac > 4) {
        if (strcmp(av[4], BROADCASTOPT) == 0)
            arp->broadcast_opt = 1;
        if (strcmp(av[4], SPOOFOPT) == 0) {
            arp->spoof_opt = 1;
            arp->mac_address = strdup(av[5]);
        }
    }
    return arp;
}

void usage(char *name)
{
    printf("%s: 'source_ip' 'dest_ip' 'iface' [--printBroadcast]", name);
    printf("[--printSpoof ['macaddr']\n");
}

int check_args(int ac, char **av)
{
    if (ac < 4 || ac > 6)
        return 1;
    if (ac > 4) {
        if (strcmp(av[4], BROADCASTOPT) != 0 && strcmp(av[4], SPOOFOPT) != 0)
            return 1;
        if ((strcmp(av[4], BROADCASTOPT) == 0 && ac != 5) ||
        (strcmp(av[4], SPOOFOPT) == 0 && ac != 6)) {
            return 1;
        }
    }
    return 0;
}