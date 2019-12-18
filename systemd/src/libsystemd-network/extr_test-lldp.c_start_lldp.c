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
typedef  int /*<<< orphan*/  sd_lldp_callback_t ;
typedef  int /*<<< orphan*/  sd_lldp ;
typedef  int /*<<< orphan*/  sd_event ;

/* Variables and functions */
 int sd_lldp_attach_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_lldp_new (int /*<<< orphan*/ **) ; 
 int sd_lldp_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int sd_lldp_set_ifindex (int /*<<< orphan*/ *,int) ; 
 int sd_lldp_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_lldp(sd_lldp **lldp, sd_event *e, sd_lldp_callback_t cb, void *cb_data) {
        int r;

        r = sd_lldp_new(lldp);
        if (r < 0)
                return r;

        r = sd_lldp_set_ifindex(*lldp, 42);
        if (r < 0)
                return r;

        r = sd_lldp_set_callback(*lldp, cb, cb_data);
        if (r < 0)
                return r;

        r = sd_lldp_attach_event(*lldp, e, 0);
        if (r < 0)
                return r;

        r = sd_lldp_start(*lldp);
        if (r < 0)
                return r;

        return 0;
}