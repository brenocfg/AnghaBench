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
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t numpeers; TYPE_1__* group; } ;
struct TYPE_4__ {int /*<<< orphan*/  real_pk; } ;
typedef  TYPE_2__ Group_c ;

/* Variables and functions */
 scalar_t__ id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int peer_in_chat(const Group_c *chat, const uint8_t *real_pk)
{
    uint32_t i;

    for (i = 0; i < chat->numpeers; ++i)
        if (id_equal(chat->group[i].real_pk, real_pk))
            return i;

    return -1;
}