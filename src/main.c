/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** main.c
*/

#include "arpspoof.h"

int main(int ac, char **av)
{
    if (check_args(ac, av) == 1) {
        usage(av[0]);
        return 84;
    }
    return (my_arpspoof(parse(ac, av)));
}