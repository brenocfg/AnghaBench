#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int vlc; } ;
typedef  TYPE_1__ dvb_int_map_t ;

/* Variables and functions */

__attribute__((used)) static int icmp (const void *a, const void *b)
{
    const int *key = a;
    const dvb_int_map_t *entry = b;
    return *key - entry->vlc;
}