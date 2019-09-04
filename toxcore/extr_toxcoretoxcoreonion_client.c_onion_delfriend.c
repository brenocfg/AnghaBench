#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_5__ {unsigned int num_friends; TYPE_2__* friends_list; } ;
typedef  int /*<<< orphan*/  Onion_Friend ;
typedef  TYPE_1__ Onion_Client ;

/* Variables and functions */
 int /*<<< orphan*/  realloc_onion_friends (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  sodium_memzero (TYPE_2__*,int) ; 

int onion_delfriend(Onion_Client *onion_c, int friend_num)
{
    if ((uint32_t)friend_num >= onion_c->num_friends)
        return -1;

    //if (onion_c->friends_list[friend_num].know_dht_public_key)
    //    DHT_delfriend(onion_c->dht, onion_c->friends_list[friend_num].dht_public_key, 0);

    sodium_memzero(&(onion_c->friends_list[friend_num]), sizeof(Onion_Friend));
    unsigned int i;

    for (i = onion_c->num_friends; i != 0; --i) {
        if (onion_c->friends_list[i - 1].status != 0)
            break;
    }

    if (onion_c->num_friends != i) {
        onion_c->num_friends = i;
        realloc_onion_friends(onion_c, onion_c->num_friends);
    }

    return friend_num;
}