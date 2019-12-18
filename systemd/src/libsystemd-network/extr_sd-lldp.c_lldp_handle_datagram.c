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
typedef  int /*<<< orphan*/  sd_lldp ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int lldp_add_neighbor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lldp_neighbor_parse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_lldp (char*) ; 
 int /*<<< orphan*/  log_lldp_errno (int,char*) ; 

__attribute__((used)) static int lldp_handle_datagram(sd_lldp *lldp, sd_lldp_neighbor *n) {
        int r;

        assert(lldp);
        assert(n);

        r = lldp_neighbor_parse(n);
        if (r == -EBADMSG) /* Ignore bad messages */
                return 0;
        if (r < 0)
                return r;

        r = lldp_add_neighbor(lldp, n);
        if (r < 0) {
                log_lldp_errno(r, "Failed to add datagram. Ignoring.");
                return 0;
        }

        log_lldp("Successfully processed LLDP datagram.");
        return 0;
}