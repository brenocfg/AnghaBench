#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {size_t numpeers; TYPE_1__* group; } ;
struct TYPE_4__ {scalar_t__ peer_number; } ;
typedef  TYPE_2__ Group_c ;

/* Variables and functions */

__attribute__((used)) static int get_peer_index(Group_c *g, uint16_t peer_number)
{
    uint32_t i;

    for (i = 0; i < g->numpeers; ++i)
        if (g->group[i].peer_number == peer_number)
            return i;

    return -1;
}