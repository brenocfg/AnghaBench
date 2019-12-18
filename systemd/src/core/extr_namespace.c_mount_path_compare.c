#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mode; } ;
typedef  TYPE_1__ MountEntry ;

/* Variables and functions */
 int CMP (int,int) ; 
 int /*<<< orphan*/  mount_entry_path (TYPE_1__ const*) ; 
 int path_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_path_compare(const MountEntry *a, const MountEntry *b) {
        int d;

        /* If the paths are not equal, then order prefixes first */
        d = path_compare(mount_entry_path(a), mount_entry_path(b));
        if (d != 0)
                return d;

        /* If the paths are equal, check the mode */
        return CMP((int) a->mode, (int) b->mode);
}