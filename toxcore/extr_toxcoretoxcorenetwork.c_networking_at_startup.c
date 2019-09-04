#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int at_startup_ran ; 
 scalar_t__ current_time_actual () ; 
 int /*<<< orphan*/  sodium_init () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 

int networking_at_startup(void)
{
    if (at_startup_ran != 0)
        return 0;

#ifndef VANILLA_NACL

#ifdef USE_RANDOMBYTES_STIR
    randombytes_stir();
#else
    sodium_init();
#endif /*USE_RANDOMBYTES_STIR*/

#endif/*VANILLA_NACL*/

#if defined(_WIN32) || defined(__WIN32__) || defined (WIN32)
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
        return -1;

#endif
    srand((uint32_t)current_time_actual());
    at_startup_ran = 1;
    return 0;
}