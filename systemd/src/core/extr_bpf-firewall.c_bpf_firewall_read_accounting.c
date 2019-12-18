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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  MAP_KEY_BYTES ; 
 int /*<<< orphan*/  MAP_KEY_PACKETS ; 
 int bpf_map_lookup_element (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bpf_firewall_read_accounting(int map_fd, uint64_t *ret_bytes, uint64_t *ret_packets) {
        uint64_t key, packets;
        int r;

        if (map_fd < 0)
                return -EBADF;

        if (ret_packets) {
                key = MAP_KEY_PACKETS;
                r = bpf_map_lookup_element(map_fd, &key, &packets);
                if (r < 0)
                        return r;
        }

        if (ret_bytes) {
                key = MAP_KEY_BYTES;
                r = bpf_map_lookup_element(map_fd, &key, ret_bytes);
                if (r < 0)
                        return r;
        }

        if (ret_packets)
                *ret_packets = packets;

        return 0;
}