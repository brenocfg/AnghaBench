#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 scalar_t__ DHT_isconnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doMessenger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m ; 

void do_tox(DHT *dht)
{
    static int dht_on = 0;

    if (!dht_on && DHT_isconnected(dht)) {
        dht_on = 1;
    } else if (dht_on && !DHT_isconnected(dht)) {
        dht_on = 0;
    }

    doMessenger(m);
}