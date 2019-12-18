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
struct TYPE_6__ {int tar_pid; scalar_t__ path; scalar_t__ buffer; int /*<<< orphan*/  tar_fd; int /*<<< orphan*/  event; int /*<<< orphan*/  compress; scalar_t__ temp_path; int /*<<< orphan*/  output_event_source; } ;
typedef  TYPE_1__ TarExport ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_REMOVE_QUOTA ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  btrfs_subvol_remove (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  import_compress_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_and_sigcont (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_terminate (int,int /*<<< orphan*/ *) ; 

TarExport *tar_export_unref(TarExport *e) {
        if (!e)
                return NULL;

        sd_event_source_unref(e->output_event_source);

        if (e->tar_pid > 1) {
                (void) kill_and_sigcont(e->tar_pid, SIGKILL);
                (void) wait_for_terminate(e->tar_pid, NULL);
        }

        if (e->temp_path) {
                (void) btrfs_subvol_remove(e->temp_path, BTRFS_REMOVE_QUOTA);
                free(e->temp_path);
        }

        import_compress_free(&e->compress);

        sd_event_unref(e->event);

        safe_close(e->tar_fd);

        free(e->buffer);
        free(e->path);
        return mfree(e);
}