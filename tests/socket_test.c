/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** socket_test.c
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "arpspoof.h"

Test(socket, t)
{
    int sock = create_socket();

    cr_assert_gt(sock, 2, "(%d > 2) is false", sock);
    close(sock);
}
