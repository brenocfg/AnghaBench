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
typedef  scalar_t__ sd_lldp_event ;
typedef  int /*<<< orphan*/  sd_lldp ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 scalar_t__ SD_LLDP_EVENT_ADDED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ link_lldp_emit_enabled (int /*<<< orphan*/ *) ; 
 int link_lldp_emit_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_lldp_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_link_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  log_link_warning_errno (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void lldp_handler(sd_lldp *lldp, sd_lldp_event event, sd_lldp_neighbor *n, void *userdata) {
        Link *link = userdata;
        int r;

        assert(link);

        (void) link_lldp_save(link);

        if (link_lldp_emit_enabled(link) && event == SD_LLDP_EVENT_ADDED) {
                /* If we received information about a new neighbor, restart the LLDP "fast" logic */

                log_link_debug(link, "Received LLDP datagram from previously unknown neighbor, restarting 'fast' LLDP transmission.");

                r = link_lldp_emit_start(link);
                if (r < 0)
                        log_link_warning_errno(link, r, "Failed to restart LLDP transmission: %m");
        }
}