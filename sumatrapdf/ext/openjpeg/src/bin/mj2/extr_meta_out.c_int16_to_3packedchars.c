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

void int16_to_3packedchars(short int value, char* buf)
{
    /* This is to retrieve the 3-letter ASCII language code */
    /* Each char is packed into 5 bits, as difference from 0x60 */
    int i;
    for (i = 2; i >= 0; i--) {
        buf[i] = (value & 0x001f) + 0x60;
        value = (value >> 5);
    }
    buf[3] = '\0';
}