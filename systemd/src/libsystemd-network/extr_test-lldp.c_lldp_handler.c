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
typedef  int /*<<< orphan*/  sd_lldp_neighbor ;
typedef  int /*<<< orphan*/  sd_lldp_event ;
typedef  int /*<<< orphan*/  sd_lldp ;

/* Variables and functions */
 int /*<<< orphan*/  lldp_handler_calls ; 

__attribute__((used)) static void lldp_handler(sd_lldp *lldp, sd_lldp_event event, sd_lldp_neighbor *n, void *userdata) {
        lldp_handler_calls++;
}