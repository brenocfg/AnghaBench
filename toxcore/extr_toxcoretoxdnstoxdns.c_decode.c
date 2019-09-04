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
typedef  char uint8_t ;

/* Variables and functions */

__attribute__((used)) static int decode(uint8_t *dest, uint8_t *src)
{
    uint8_t *p = src, *op = dest, bits = 0;
    *op = 0;

    while (*p) {
        uint8_t ch = *p++;

        if ('A' <= ch && ch <= 'Z') {
            ch = ch - 'A';
        } else if ('a' <= ch && ch <= 'z') {
            ch = ch - 'a';
        } else if ('0' <= ch && ch <= '5') {
            ch = ch - '0' + 26;
        } else {
            return - 1;
        }

        *op |= (ch << bits);
        bits += 5;

        if (bits >= 8) {
            bits -= 8;
            ++op;
            *op = (ch >> (5 - bits));
        }
    }

    return op - dest;
}