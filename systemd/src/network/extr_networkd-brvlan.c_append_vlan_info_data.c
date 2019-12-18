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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct bridge_vlan_info {int vid; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  br_vlan ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int BRIDGE_VLAN_BITMAP_LEN ; 
 int /*<<< orphan*/  BRIDGE_VLAN_INFO_PVID ; 
 int /*<<< orphan*/  BRIDGE_VLAN_INFO_RANGE_BEGIN ; 
 int /*<<< orphan*/  BRIDGE_VLAN_INFO_RANGE_END ; 
 int /*<<< orphan*/  BRIDGE_VLAN_INFO_UNTAGGED ; 
 int /*<<< orphan*/  IFLA_BRIDGE_VLAN_INFO ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int find_next_bit (int,int /*<<< orphan*/ ) ; 
 int is_bit_set (int,int /*<<< orphan*/ ) ; 
 int log_link_error_errno (int /*<<< orphan*/ * const,int,char*) ; 
 int sd_netlink_message_append_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bridge_vlan_info*,int) ; 

__attribute__((used)) static int append_vlan_info_data(Link *const link, sd_netlink_message *req, uint16_t pvid, const uint32_t *br_vid_bitmap, const uint32_t *br_untagged_bitmap) {
        struct bridge_vlan_info br_vlan;
        int i, j, k, r, cnt;
        uint16_t begin, end;
        bool done, untagged = false;

        assert(link);
        assert(req);
        assert(br_vid_bitmap);
        assert(br_untagged_bitmap);

        cnt = 0;

        begin = end = UINT16_MAX;
        for (k = 0; k < BRIDGE_VLAN_BITMAP_LEN; k++) {
                unsigned base_bit;
                uint32_t vid_map = br_vid_bitmap[k];
                uint32_t untagged_map = br_untagged_bitmap[k];

                base_bit = k * 32;
                i = -1;
                done = false;
                do {
                        j = find_next_bit(i, vid_map);
                        if (j > 0) {
                                /* first hit of any bit */
                                if (begin == UINT16_MAX && end == UINT16_MAX) {
                                        begin = end = j - 1 + base_bit;
                                        untagged = is_bit_set(j - 1, untagged_map);
                                        goto next;
                                }

                                /* this bit is a continuation of prior bits */
                                if (j - 2 + base_bit == end && untagged == is_bit_set(j - 1, untagged_map) && (uint16_t)j - 1 + base_bit != pvid && (uint16_t)begin != pvid) {
                                        end++;
                                        goto next;
                                }
                        } else
                                done = true;

                        if (begin != UINT16_MAX) {
                                cnt++;
                                if (done && k < BRIDGE_VLAN_BITMAP_LEN - 1)
                                        break;

                                br_vlan.flags = 0;
                                if (untagged)
                                        br_vlan.flags |= BRIDGE_VLAN_INFO_UNTAGGED;

                                if (begin == end) {
                                        br_vlan.vid = begin;

                                        if (begin == pvid)
                                                br_vlan.flags |= BRIDGE_VLAN_INFO_PVID;

                                        r = sd_netlink_message_append_data(req, IFLA_BRIDGE_VLAN_INFO, &br_vlan, sizeof(br_vlan));
                                        if (r < 0)
                                                return log_link_error_errno(link, r, "Could not append IFLA_BRIDGE_VLAN_INFO attribute: %m");
                                } else {
                                        br_vlan.vid = begin;
                                        br_vlan.flags |= BRIDGE_VLAN_INFO_RANGE_BEGIN;

                                        r = sd_netlink_message_append_data(req, IFLA_BRIDGE_VLAN_INFO, &br_vlan, sizeof(br_vlan));
                                        if (r < 0)
                                                return log_link_error_errno(link, r, "Could not append IFLA_BRIDGE_VLAN_INFO attribute: %m");

                                        br_vlan.vid = end;
                                        br_vlan.flags &= ~BRIDGE_VLAN_INFO_RANGE_BEGIN;
                                        br_vlan.flags |= BRIDGE_VLAN_INFO_RANGE_END;

                                        r = sd_netlink_message_append_data(req, IFLA_BRIDGE_VLAN_INFO, &br_vlan, sizeof(br_vlan));
                                        if (r < 0)
                                                return log_link_error_errno(link, r, "Could not append IFLA_BRIDGE_VLAN_INFO attribute: %m");
                                }

                                if (done)
                                        break;
                        }
                        if (j > 0) {
                                begin = end = j - 1 + base_bit;
                                untagged = is_bit_set(j - 1, untagged_map);
                        }

                next:
                        i = j;
                } while (!done);
        }

        assert(cnt > 0);
        return cnt;
}