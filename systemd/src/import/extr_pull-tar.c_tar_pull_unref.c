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
struct TYPE_6__ {int tar_pid; scalar_t__ local; scalar_t__ image_root; scalar_t__ settings_path; scalar_t__ final_path; scalar_t__ settings_temp_path; scalar_t__ temp_path; int /*<<< orphan*/  event; int /*<<< orphan*/  glue; int /*<<< orphan*/  signature_job; int /*<<< orphan*/  checksum_job; int /*<<< orphan*/  settings_job; int /*<<< orphan*/  tar_job; } ;
typedef  TYPE_1__ TarPull ;

/* Variables and functions */
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 int REMOVE_SUBVOLUME ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  curl_glue_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  kill_and_sigcont (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pull_job_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_rf (scalar_t__,int) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 
 int /*<<< orphan*/  wait_for_terminate (int,int /*<<< orphan*/ *) ; 

TarPull* tar_pull_unref(TarPull *i) {
        if (!i)
                return NULL;

        if (i->tar_pid > 1) {
                (void) kill_and_sigcont(i->tar_pid, SIGKILL);
                (void) wait_for_terminate(i->tar_pid, NULL);
        }

        pull_job_unref(i->tar_job);
        pull_job_unref(i->settings_job);
        pull_job_unref(i->checksum_job);
        pull_job_unref(i->signature_job);

        curl_glue_unref(i->glue);
        sd_event_unref(i->event);

        if (i->temp_path) {
                (void) rm_rf(i->temp_path, REMOVE_ROOT|REMOVE_PHYSICAL|REMOVE_SUBVOLUME);
                free(i->temp_path);
        }

        if (i->settings_temp_path) {
                (void) unlink(i->settings_temp_path);
                free(i->settings_temp_path);
        }

        free(i->final_path);
        free(i->settings_path);
        free(i->image_root);
        free(i->local);

        return mfree(i);
}