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
typedef  int u_int64_t ;

/* Variables and functions */
 int INT64 (int) ; 

void polymult (u_int64_t *php, u_int64_t *plp, u_int64_t x, u_int64_t y)
{
    int i;
    u_int64_t ph = 0, pl = 0;
    if (x & 1)
        pl = y;
    for (i = 1; i < 64; i++)
        if (x & (INT64 (1) << i)) {
            ph ^= y >> (64 - i);
            pl ^= y << i;
        }
    if (php)
        *php = ph;
    if (plp)
        *plp = pl;
}