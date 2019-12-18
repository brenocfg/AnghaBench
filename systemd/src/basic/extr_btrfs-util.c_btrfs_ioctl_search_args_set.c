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
struct TYPE_2__ {int /*<<< orphan*/  min_offset; int /*<<< orphan*/  min_type; int /*<<< orphan*/  min_objectid; } ;
struct btrfs_ioctl_search_header {int /*<<< orphan*/  offset; TYPE_1__ key; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
typedef  struct btrfs_ioctl_search_args {int /*<<< orphan*/  offset; TYPE_1__ key; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } const btrfs_ioctl_search_args ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct btrfs_ioctl_search_header const*) ; 

__attribute__((used)) static void btrfs_ioctl_search_args_set(struct btrfs_ioctl_search_args *args, const struct btrfs_ioctl_search_header *h) {
        assert(args);
        assert(h);

        args->key.min_objectid = h->objectid;
        args->key.min_type = h->type;
        args->key.min_offset = h->offset;
}