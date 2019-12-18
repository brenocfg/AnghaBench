#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ inotify_fd; int /*<<< orphan*/  directories_by_wd; } ;
typedef  TYPE_1__ sd_journal ;

/* Variables and functions */
 int IN_CLOEXEC ; 
 int IN_NONBLOCK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int errno ; 
 int hashmap_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ inotify_init1 (int) ; 

__attribute__((used)) static int allocate_inotify(sd_journal *j) {
        assert(j);

        if (j->inotify_fd < 0) {
                j->inotify_fd = inotify_init1(IN_NONBLOCK|IN_CLOEXEC);
                if (j->inotify_fd < 0)
                        return -errno;
        }

        return hashmap_ensure_allocated(&j->directories_by_wd, NULL);
}