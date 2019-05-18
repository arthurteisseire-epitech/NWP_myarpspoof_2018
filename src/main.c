/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** main.c
*/

#include <stdlib.h>
#include "arpspoof.h"

static void free_arp(arp_t *arp)
{
    free(arp->dest_ip);
    free(arp->iface);
    free(arp->mac_address);
    free(arp->source_ip);
    free(arp);
}

static int my_arpspoof(arp_t *arp)
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

int main(int ac, char **av)
{
    if (check_args(ac, av) == 1) {
        usage(av[0]);
        return 84;
    }
    return my_arpspoof(parse(ac, av));
}