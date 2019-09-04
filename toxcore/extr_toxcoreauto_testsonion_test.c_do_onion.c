#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dht; int /*<<< orphan*/  net; } ;
typedef  TYPE_1__ Onion ;

/* Variables and functions */
 int /*<<< orphan*/  do_DHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  networking_poll (int /*<<< orphan*/ ) ; 

void do_onion(Onion *onion)
{
    networking_poll(onion->net);
    do_DHT(onion->dht);
}