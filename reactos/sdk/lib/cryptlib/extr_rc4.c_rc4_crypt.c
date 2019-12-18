#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* state; unsigned int x; unsigned int y; } ;
typedef  TYPE_1__ RC4_CONTEXT ;

/* Variables and functions */

void rc4_crypt(RC4_CONTEXT *a4i, unsigned char *inoutString, unsigned int length)
{
    unsigned char *const s=a4i->state;
    unsigned int x = a4i->x;
    unsigned int y = a4i->y;
    unsigned int a, b;

    while(length--)
    {
        x = (x+1) & 0xff;
        a = s[x];
        y = (y+a) & 0xff;
        b = s[y];
        s[x] = b;
        s[y] = a;
        *inoutString++ ^= s[(a+b) & 0xff];
    }

    a4i->x = x;
    a4i->y = y;
}