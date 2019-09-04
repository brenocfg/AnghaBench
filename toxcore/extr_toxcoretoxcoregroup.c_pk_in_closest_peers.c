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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* closest_peers; } ;
struct TYPE_4__ {int /*<<< orphan*/  real_pk; int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ Group_c ;

/* Variables and functions */
 unsigned int DESIRED_CLOSE_CONNECTIONS ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int pk_in_closest_peers(Group_c *g, uint8_t *real_pk)
{
    unsigned int i;

    for (i = 0; i < DESIRED_CLOSE_CONNECTIONS; ++i) {
        if (!g->closest_peers[i].entry)
            continue;

        if (public_key_cmp(g->closest_peers[i].real_pk, real_pk) == 0)
            return 1;

    }

    return 0;
}