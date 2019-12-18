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
struct TYPE_4__ {int /*<<< orphan*/  acd; } ;
typedef  TYPE_1__ sd_ipv4ll ;

/* Variables and functions */
 int /*<<< orphan*/  assert_return (TYPE_1__*,int) ; 
 int sd_ipv4acd_is_running (int /*<<< orphan*/ ) ; 

int sd_ipv4ll_is_running(sd_ipv4ll *ll) {
        assert_return(ll, false);

        return sd_ipv4acd_is_running(ll->acd);
}