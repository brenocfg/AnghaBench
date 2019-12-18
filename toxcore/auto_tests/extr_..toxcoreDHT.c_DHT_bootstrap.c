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
struct TYPE_4__ {int /*<<< orphan*/  self_public_key; } ;
typedef  int /*<<< orphan*/  IP_Port ;
typedef  TYPE_1__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  getnodes (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void DHT_bootstrap(DHT *dht, IP_Port ip_port, const uint8_t *public_key)
{
    /*#ifdef ENABLE_ASSOC_DHT
       if (dht->assoc) {
           IPPTs ippts;
           ippts.ip_port = ip_port;
           ippts.timestamp = 0;

           Assoc_add_entry(dht->assoc, public_key, &ippts, NULL, 0);
       }
       #endif*/

    getnodes(dht, ip_port, public_key, dht->self_public_key, NULL);
}