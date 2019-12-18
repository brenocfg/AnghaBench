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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  sd_lldp_neighbor ;
typedef  int /*<<< orphan*/  sd_lldp ;
typedef  int /*<<< orphan*/  sd_event ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  lldp_handler ; 
 scalar_t__ lldp_handler_calls ; 
 int /*<<< orphan*/  sd_event_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_lldp_get_neighbors (int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ; 
 scalar_t__ start_lldp (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stop_lldp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_fd ; 
 int write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void test_receive_incomplete_packet(sd_event *e) {
        sd_lldp *lldp;
        sd_lldp_neighbor **neighbors;
        uint8_t frame[] = {
                /* Ethernet header */
                0x01, 0x80, 0xc2, 0x00, 0x00, 0x03,     /* Destination MAC */
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06,     /* Source MAC */
                0x88, 0xcc,                             /* Ethertype */
                /* LLDP mandatory TLVs */
                0x02, 0x07, 0x04, 0x00, 0x01, 0x02,     /* Chassis: MAC, 00:01:02:03:04:05 */
                0x03, 0x04, 0x05,
                0x04, 0x04, 0x05, 0x31, 0x2f, 0x33,     /* Port: interface name, "1/3" */
                                                        /* Missing TTL */
                0x00, 0x00                              /* End Of LLDPDU */
        };

        lldp_handler_calls = 0;
        assert_se(start_lldp(&lldp, e, lldp_handler, NULL) == 0);

        assert_se(write(test_fd[1], frame, sizeof(frame)) == sizeof(frame));
        sd_event_run(e, 0);
        assert_se(lldp_handler_calls == 0);
        assert_se(sd_lldp_get_neighbors(lldp, &neighbors) == 0);

        assert_se(stop_lldp(lldp) == 0);
}