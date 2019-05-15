/*
** EPITECH PROJECT, 2018
** myARPspoof
** File description:
** mac_address.c
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "arpspoof.h"

Test(Good_mac_address, t)
{
    const char *mac_addr = "aa:bb:cc:dd:ee:ff";

    cr_assert_eq(is_mac_addr(mac_addr), 1, "Expected 1, got : %d",
        is_mac_addr(mac_addr));
}

Test(Bad_mac_addr, t)
{
    const char *mac_addr = "aa:bb:cc:dd:ee:fg";

    cr_assert_eq(is_mac_addr(mac_addr), 0, "Expected 0, got : %d",
        is_mac_addr(mac_addr));
}