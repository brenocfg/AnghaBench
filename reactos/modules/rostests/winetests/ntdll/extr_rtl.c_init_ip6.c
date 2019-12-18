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
struct TYPE_3__ {int* s6_words; } ;
typedef  TYPE_1__ IN6_ADDR ;

/* Variables and functions */

__attribute__((used)) static void init_ip6(IN6_ADDR* addr, const int src[8])
{
    unsigned int j;
    if (!src || src[0] == -1)
    {
        for (j = 0; j < 8; ++j)
            addr->s6_words[j] = 0xabab;
    }
    else
    {
        for (j = 0; j < 8; ++j)
            addr->s6_words[j] = src[j];
    }
}