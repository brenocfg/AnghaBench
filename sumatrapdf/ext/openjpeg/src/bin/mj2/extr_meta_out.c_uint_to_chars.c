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

/* Variables and functions */

void uint_to_chars(unsigned int value, char* buf)
{
    /* buf is at least char[5] */
    int i;
    for (i = 3; i >= 0; i--) {
        buf[i] = (value & 0x000000ff);
        value = (value >> 8);
    }
    buf[4] = '\0'; /* Precautionary */
}