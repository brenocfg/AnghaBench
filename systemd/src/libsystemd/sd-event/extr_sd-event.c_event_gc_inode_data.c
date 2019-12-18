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
struct inotify_data {int /*<<< orphan*/  inodes; } ;
struct inode_data {struct inotify_data* inotify_data; scalar_t__ event_sources; } ;
typedef  int /*<<< orphan*/  sd_event ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_free_inode_data (int /*<<< orphan*/ *,struct inode_data*) ; 
 int /*<<< orphan*/  event_free_inotify_data (int /*<<< orphan*/ *,struct inotify_data*) ; 
 scalar_t__ hashmap_isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void event_gc_inode_data(
                sd_event *e,
                struct inode_data *d) {

        struct inotify_data *inotify_data;

        assert(e);

        if (!d)
                return;

        if (d->event_sources)
                return;

        inotify_data = d->inotify_data;
        event_free_inode_data(e, d);

        if (inotify_data && hashmap_isempty(inotify_data->inodes))
                event_free_inotify_data(e, inotify_data);
}