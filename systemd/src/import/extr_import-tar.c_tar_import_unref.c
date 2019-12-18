#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tar_pid; scalar_t__ local; scalar_t__ image_root; scalar_t__ final_path; int /*<<< orphan*/  tar_fd; int /*<<< orphan*/  event; int /*<<< orphan*/  compress; scalar_t__ temp_path; int /*<<< orphan*/  input_event_source; } ;
typedef  TYPE_1__ TarImport ;

/* Variables and functions */
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 int REMOVE_SUBVOLUME ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  import_compress_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_and_sigcont (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  rm_rf (scalar_t__,int) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_terminate (int,int /*<<< orphan*/ *) ; 

TarImport* tar_import_unref(TarImport *i) {
        if (!i)
                return NULL;

        sd_event_source_unref(i->input_event_source);

        if (i->tar_pid > 1) {
                (void) kill_and_sigcont(i->tar_pid, SIGKILL);
                (void) wait_for_terminate(i->tar_pid, NULL);
        }

        if (i->temp_path) {
                (void) rm_rf(i->temp_path, REMOVE_ROOT|REMOVE_PHYSICAL|REMOVE_SUBVOLUME);
                free(i->temp_path);
        }

        import_compress_free(&i->compress);

        sd_event_unref(i->event);

        safe_close(i->tar_fd);

        free(i->final_path);
        free(i->image_root);
        free(i->local);
        return mfree(i);
}