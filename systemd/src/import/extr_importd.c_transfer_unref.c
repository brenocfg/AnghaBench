#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pid; int /*<<< orphan*/  stdout_fd; int /*<<< orphan*/  stdin_fd; int /*<<< orphan*/  log_fd; int /*<<< orphan*/  object_path; int /*<<< orphan*/  format; int /*<<< orphan*/  local; int /*<<< orphan*/  remote; int /*<<< orphan*/  log_event_source; int /*<<< orphan*/  pid_event_source; int /*<<< orphan*/  id; TYPE_1__* manager; } ;
typedef  TYPE_2__ Transfer ;
struct TYPE_7__ {int /*<<< orphan*/  transfers; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  UINT32_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_and_sigcont (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_terminate (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Transfer *transfer_unref(Transfer *t) {
        if (!t)
                return NULL;

        if (t->manager)
                hashmap_remove(t->manager->transfers, UINT32_TO_PTR(t->id));

        sd_event_source_unref(t->pid_event_source);
        sd_event_source_unref(t->log_event_source);

        free(t->remote);
        free(t->local);
        free(t->format);
        free(t->object_path);

        if (t->pid > 0) {
                (void) kill_and_sigcont(t->pid, SIGKILL);
                (void) wait_for_terminate(t->pid, NULL);
        }

        safe_close(t->log_fd);
        safe_close(t->stdin_fd);
        safe_close(t->stdout_fd);

        return mfree(t);
}