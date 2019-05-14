/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** arpspoof
*/

#ifndef ARPSPOOF_H_
#define ARPSPOOF_H_

#include <netpacket/packet.h>
#include <netinet/ether.h>

#define SPOOFOPT "--printSpoof"
#define BROADCASTOPT "--printBroadcast"

typedef struct arp {
    char *source_ip;
    char *dest_ip;
    char *iface;
    char broadcast_opt;
    char spoof_opt;
    char *mac_address;
} arp_t;

arp_t *parse(int ac, char **av);
int check_args(int ac, char **av);
void usage(char *name);
int create_socket();
int my_arpspoof(arp_t *arp);
struct sockaddr_ll create_dest_address(int sockfd, const char *if_name);
void init_ethernet_frame(struct ether_arp *hdr);

#endif /* !ARPSPOOF_H_ */
