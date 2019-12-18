#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  dht; } ;
typedef  TYPE_1__ Onion_Client ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int DHT_getfriendip (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ onion_getfriend_DHT_pubkey (TYPE_1__ const*,int,int /*<<< orphan*/ *) ; 

int onion_getfriendip(const Onion_Client *onion_c, int friend_num, IP_Port *ip_port)
{
    uint8_t dht_public_key[crypto_box_PUBLICKEYBYTES];

    if (onion_getfriend_DHT_pubkey(onion_c, friend_num, dht_public_key) == 0)
        return -1;

    return DHT_getfriendip(onion_c->dht, dht_public_key, ip_port);
}