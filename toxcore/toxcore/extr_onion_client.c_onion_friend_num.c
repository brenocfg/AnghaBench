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
struct TYPE_5__ {unsigned int num_friends; TYPE_1__* friends_list; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  real_public_key; } ;
typedef  TYPE_2__ Onion_Client ;

/* Variables and functions */
 scalar_t__ public_key_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int onion_friend_num(const Onion_Client *onion_c, const uint8_t *public_key)
{
    unsigned int i;

    for (i = 0; i < onion_c->num_friends; ++i) {
        if (onion_c->friends_list[i].status == 0)
            continue;

        if (public_key_cmp(public_key, onion_c->friends_list[i].real_public_key) == 0)
            return i;
    }

    return -1;
}