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
union bpf_attr {int map_type; size_t key_size; size_t value_size; size_t max_entries; int /*<<< orphan*/  map_flags; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum bpf_map_type { ____Placeholder_bpf_map_type } bpf_map_type ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_CREATE ; 
 int bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 
 int errno ; 

int bpf_map_new(enum bpf_map_type type, size_t key_size, size_t value_size, size_t max_entries, uint32_t flags) {
        union bpf_attr attr = {
                .map_type = type,
                .key_size = key_size,
                .value_size = value_size,
                .max_entries = max_entries,
                .map_flags = flags,
        };
        int fd;

        fd = bpf(BPF_MAP_CREATE, &attr, sizeof(attr));
        if (fd < 0)
                return -errno;

        return fd;
}