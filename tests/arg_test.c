/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** arg_test
*/

#include <criterion/criterion.h>
#include "arpspoof.h"

Test(badArgument, t)
{
    char *av[] = {"./myARPspoof", "toto"};
    int ac = 2;
    int result = check_args(ac, av);
    cr_assert_eq(result, 1, "%d\n", result);
}

Test(goodArgumentBase, t)
{
    char *av[] = {"./myARPspoof", "42.42.42.42", "192.168.0.1", "wlo1"};
    int ac = 4;
    int result = check_args(ac, av);
    cr_assert_eq(result, 0, "Expected : 0, got: %d", result);
}

Test(goodArgumentBroadcast, t)
{
    char *av[] = {"./myARPspoof", "42.42.42.42", "192.168.0.1", "wlo1",
    BROADCASTOPT};
    int ac = 5;
    int result = check_args(ac, av);
    cr_assert_eq(result, 0, "Expected : 0, got: %d", result);
}

Test(badArgumentBroadcast, t)
{
    char *av[] = {"./myARPspoof", "42.42.42.42", "192.168.0.1", "wlo1",
    "--printBroadcast", "toto"};
    int ac = 6;
    int result = check_args(ac, av);
    cr_assert_eq(result, 1, "Expected : 1, got: %d", result);
}

Test(badArgumentSpoof, t)
{
    char *av[] = {"./myARPspoof", "42.42.42.42", "192.168.0.1", "wlo1",
    "--printSpoof"};
    int ac = 5;
    int result = check_args(ac, av);
    cr_assert_eq(result, 1, "Expected : 1, got: %d", result);
}