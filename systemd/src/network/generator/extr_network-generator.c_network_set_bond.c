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
struct TYPE_4__ {int /*<<< orphan*/  bond; } ;
typedef  TYPE_1__ Network ;
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* network_get (int /*<<< orphan*/ *,char const*) ; 
 int network_new (int /*<<< orphan*/ *,char const*,TYPE_1__**) ; 

__attribute__((used)) static int network_set_bond(Context *context, const char *ifname, const char *value) {
        Network *network;
        int r;

        network = network_get(context, ifname);
        if (!network) {
                r = network_new(context, ifname, &network);
                if (r < 0)
                        return r;
        }

        return free_and_strdup(&network->bond, value);
}