/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** mac_to_char6.c
*/

#include <criterion/criterion.h>
#include "arpspoof.h"

Test(mac_to_char6, simple)
{
    const unsigned char mac[] = "ab:ba:00:12:89:78";
    unsigned char actual[6];
    const unsigned char expected[6] = {0xab, 0xba, 0x0, 0x12, 0x89, 0x78};

    mac_to_char6(mac, actual);
    cr_assert_arr_eq(expected, actual, 6);
}
