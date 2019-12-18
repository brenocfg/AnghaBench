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
struct TYPE_2__ {int /*<<< orphan*/  max_offset; int /*<<< orphan*/  min_offset; int /*<<< orphan*/  max_type; int /*<<< orphan*/  min_type; int /*<<< orphan*/  max_objectid; int /*<<< orphan*/  min_objectid; } ;
struct btrfs_ioctl_search_args {TYPE_1__ key; } ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct btrfs_ioctl_search_args const*) ; 

__attribute__((used)) static int btrfs_ioctl_search_args_compare(const struct btrfs_ioctl_search_args *args) {
        int r;

        assert(args);

        /* Compare min and max */

        r = CMP(args->key.min_objectid, args->key.max_objectid);
        if (r != 0)
                return r;

        r = CMP(args->key.min_type, args->key.max_type);
        if (r != 0)
                return r;

        return CMP(args->key.min_offset, args->key.max_offset);
}