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
struct TYPE_4__ {scalar_t__ address; } ;
typedef  TYPE_1__ sd_ipv4ll ;

/* Variables and functions */
 int ipv4ll_start_internal (TYPE_1__*,int) ; 

int sd_ipv4ll_restart(sd_ipv4ll *ll) {
        ll->address = 0;

        return ipv4ll_start_internal(ll, false);
}