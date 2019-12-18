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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ num_friends; TYPE_1__* friends_list; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  dht_public_key; int /*<<< orphan*/  know_dht_public_key; } ;
typedef  TYPE_2__ Onion_Client ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int onion_getfriend_DHT_pubkey(const Onion_Client *onion_c, int friend_num, uint8_t *dht_key)
{
    if ((uint32_t)friend_num >= onion_c->num_friends)
        return 0;

    if (onion_c->friends_list[friend_num].status == 0)
        return 0;

    if (!onion_c->friends_list[friend_num].know_dht_public_key)
        return 0;

    memcpy(dht_key, onion_c->friends_list[friend_num].dht_public_key, crypto_box_PUBLICKEYBYTES);
    return 1;
}