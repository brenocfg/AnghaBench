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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ num_friends; TYPE_1__* friends_list; } ;
struct TYPE_4__ {int is_online; scalar_t__ run_count; scalar_t__ last_noreplay; int /*<<< orphan*/  last_seen; } ;
typedef  TYPE_2__ Onion_Client ;

/* Variables and functions */
 int /*<<< orphan*/  unix_time () ; 

int onion_set_friend_online(Onion_Client *onion_c, int friend_num, uint8_t is_online)
{
    if ((uint32_t)friend_num >= onion_c->num_friends)
        return -1;

    if (is_online == 0 && onion_c->friends_list[friend_num].is_online == 1)
        onion_c->friends_list[friend_num].last_seen = unix_time();

    onion_c->friends_list[friend_num].is_online = is_online;

    /* This should prevent some clock related issues */
    if (!is_online) {
        onion_c->friends_list[friend_num].last_noreplay = 0;
        onion_c->friends_list[friend_num].run_count = 0;
    }

    return 0;
}