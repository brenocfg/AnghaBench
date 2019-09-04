#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int* uint8; } ;
struct TYPE_13__ {TYPE_1__ ip6; } ;
struct TYPE_12__ {scalar_t__ onion_c; scalar_t__ onion_a; scalar_t__ onion; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ TCP_Proxy_Info ;
typedef  TYPE_3__ Onions ;
typedef  TYPE_4__ IP ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 int /*<<< orphan*/  ip_init (TYPE_4__*,int) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/ * new_DHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_net_crypto (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  new_networking (TYPE_4__,int /*<<< orphan*/ ) ; 
 scalar_t__ new_onion (int /*<<< orphan*/ *) ; 
 scalar_t__ new_onion_announce (int /*<<< orphan*/ *) ; 
 scalar_t__ new_onion_client (int /*<<< orphan*/ ) ; 

Onions *new_onions(uint16_t port)
{
    IP ip;
    ip_init(&ip, 1);
    ip.ip6.uint8[15] = 1;
    Onions *on = malloc(sizeof(Onions));
    DHT *dht = new_DHT(new_networking(ip, port));
    on->onion = new_onion(dht);
    on->onion_a = new_onion_announce(dht);
    TCP_Proxy_Info inf = {0};
    on->onion_c = new_onion_client(new_net_crypto(dht, &inf));

    if (on->onion && on->onion_a && on->onion_c)
        return on;

    return NULL;
}