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
struct inotify_data {scalar_t__ buffer_filled; scalar_t__ fd; int /*<<< orphan*/  priority; int /*<<< orphan*/  wd; int /*<<< orphan*/  inodes; } ;
struct TYPE_5__ {int /*<<< orphan*/  epoll_fd; int /*<<< orphan*/  inotify_data; int /*<<< orphan*/  inotify_data_buffered; } ;
typedef  TYPE_1__ sd_event ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inotify_data*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  buffered ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct inotify_data*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* hashmap_isempty (int /*<<< orphan*/ ) ; 
 struct inotify_data* hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  safe_close (scalar_t__) ; 

__attribute__((used)) static void event_free_inotify_data(sd_event *e, struct inotify_data *d) {
        assert(e);

        if (!d)
                return;

        assert(hashmap_isempty(d->inodes));
        assert(hashmap_isempty(d->wd));

        if (d->buffer_filled > 0)
                LIST_REMOVE(buffered, e->inotify_data_buffered, d);

        hashmap_free(d->inodes);
        hashmap_free(d->wd);

        assert_se(hashmap_remove(e->inotify_data, &d->priority) == d);

        if (d->fd >= 0) {
                if (epoll_ctl(e->epoll_fd, EPOLL_CTL_DEL, d->fd, NULL) < 0)
                        log_debug_errno(errno, "Failed to remove inotify fd from epoll, ignoring: %m");

                safe_close(d->fd);
        }
        free(d);
}