/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** socket.c
*/

#include <sys/socket.h>
#include <netinet/in.h>

int create_socket()
{
    int sock = socket(AF_PACKET, SOCK_RAW, IPPROTO_TCP);

    return sock;
}
