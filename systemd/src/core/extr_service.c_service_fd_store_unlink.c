#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fd; struct TYPE_7__* fdname; int /*<<< orphan*/  event_source; TYPE_1__* service; } ;
struct TYPE_6__ {scalar_t__ n_fd_store; int /*<<< orphan*/  fd_store; } ;
typedef  TYPE_2__ ServiceFDStore ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fd_store ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_disable_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_fd_store_unlink(ServiceFDStore *fs) {

        if (!fs)
                return;

        if (fs->service) {
                assert(fs->service->n_fd_store > 0);
                LIST_REMOVE(fd_store, fs->service->fd_store, fs);
                fs->service->n_fd_store--;
        }

        sd_event_source_disable_unref(fs->event_source);

        free(fs->fdname);
        safe_close(fs->fd);
        free(fs);
}