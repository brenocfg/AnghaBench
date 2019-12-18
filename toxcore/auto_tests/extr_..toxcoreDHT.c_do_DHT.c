#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ last_run; scalar_t__ assoc; int /*<<< orphan*/  ping; scalar_t__ loaded_num_nodes; } ;
typedef  TYPE_1__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  DHT_connect_after_load (TYPE_1__*) ; 
 int /*<<< orphan*/  do_Assoc (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  do_Close (TYPE_1__*) ; 
 int /*<<< orphan*/  do_DHT_friends (TYPE_1__*) ; 
 int /*<<< orphan*/  do_NAT (TYPE_1__*) ; 
 int /*<<< orphan*/  do_to_ping (int /*<<< orphan*/ ) ; 
 scalar_t__ unix_time () ; 
 int /*<<< orphan*/  unix_time_update () ; 

void do_DHT(DHT *dht)
{
    unix_time_update();

    if (dht->last_run == unix_time()) {
        return;
    }

    // Load friends/clients if first call to do_DHT
    if (dht->loaded_num_nodes) {
        DHT_connect_after_load(dht);
    }

    do_Close(dht);
    do_DHT_friends(dht);
    do_NAT(dht);
    do_to_ping(dht->ping);
    //do_hardening(dht);
#ifdef ENABLE_ASSOC_DHT

    if (dht->assoc)
        do_Assoc(dht->assoc, dht);

#endif
    dht->last_run = unix_time();
}