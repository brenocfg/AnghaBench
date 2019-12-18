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
struct TYPE_3__ {int /*<<< orphan*/  mtu; } ;
typedef  TYPE_1__ Network ;
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* network_get (int /*<<< orphan*/ *,char const*) ; 
 int parse_mtu (int,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int network_set_mtu(Context *context, const char *ifname, int family, const char *mtu) {
        Network *network;

        network = network_get(context, ifname);
        if (!network)
                return -ENODEV;

        return parse_mtu(family, mtu, &network->mtu);
}