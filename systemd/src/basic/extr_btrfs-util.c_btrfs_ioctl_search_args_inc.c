#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ min_offset; scalar_t__ min_type; scalar_t__ min_objectid; } ;
struct btrfs_ioctl_search_args {TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct btrfs_ioctl_search_args*) ; 

__attribute__((used)) static bool btrfs_ioctl_search_args_inc(struct btrfs_ioctl_search_args *args) {
        assert(args);

        /* the objectid, type, offset together make up the btrfs key,
         * which is considered a single 136byte integer when
         * comparing. This call increases the counter by one, dealing
         * with the overflow between the overflows */

        if (args->key.min_offset < (uint64_t) -1) {
                args->key.min_offset++;
                return true;
        }

        if (args->key.min_type < (uint8_t) -1) {
                args->key.min_type++;
                args->key.min_offset = 0;
                return true;
        }

        if (args->key.min_objectid < (uint64_t) -1) {
                args->key.min_objectid++;
                args->key.min_offset = 0;
                args->key.min_type = 0;
                return true;
        }

        return 0;
}