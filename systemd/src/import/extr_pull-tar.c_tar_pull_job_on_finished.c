#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;

/* Type definitions */
struct TYPE_21__ {int error; scalar_t__ style; scalar_t__ tar_pid; int /*<<< orphan*/  event; struct TYPE_21__* userdata; int /*<<< orphan*/  (* on_finished ) (TYPE_1__*,int,TYPE_1__*) ;struct TYPE_21__* settings_temp_path; struct TYPE_21__* settings_path; struct TYPE_21__* settings_job; struct TYPE_21__* temp_path; struct TYPE_21__* final_path; struct TYPE_21__* signature_job; struct TYPE_21__* checksum_job; TYPE_13__* tar_job; void* disk_fd; } ;
typedef  TYPE_1__ TarPull ;
struct TYPE_20__ {int /*<<< orphan*/  etag_exists; void* disk_fd; } ;
typedef  TYPE_1__ PullJob ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int EIO ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  TAR_COPYING ; 
 int /*<<< orphan*/  TAR_FINALIZING ; 
 int /*<<< orphan*/  TAR_VERIFYING ; 
 scalar_t__ VERIFICATION_PER_DIRECTORY ; 
 int /*<<< orphan*/  WAIT_LOG ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int import_make_read_only (TYPE_1__*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*,...) ; 
 int /*<<< orphan*/  log_info_errno (int,char*) ; 
 void* mfree (TYPE_1__*) ; 
 int pull_verify (TYPE_13__*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int rename_noreplace (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* safe_close (void*) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,TYPE_1__*) ; 
 int tar_pull_determine_path (TYPE_1__*,char*,TYPE_1__**) ; 
 int /*<<< orphan*/  tar_pull_is_done (TYPE_1__*) ; 
 int tar_pull_make_local_copy (TYPE_1__*) ; 
 int /*<<< orphan*/  tar_pull_report_progress (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int wait_for_terminate_and_check (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tar_pull_job_on_finished(PullJob *j) {
        TarPull *i;
        int r;

        assert(j);
        assert(j->userdata);

        i = j->userdata;

        if (j == i->settings_job) {
                if (j->error != 0)
                        log_info_errno(j->error, "Settings file could not be retrieved, proceeding without.");
        } else if (j->error != 0 && j != i->signature_job) {
                if (j == i->checksum_job)
                        log_error_errno(j->error, "Failed to retrieve SHA256 checksum, cannot verify. (Try --verify=no?)");
                else
                        log_error_errno(j->error, "Failed to retrieve image file. (Wrong URL?)");

                r = j->error;
                goto finish;
        }

        /* This is invoked if either the download completed
         * successfully, or the download was skipped because we
         * already have the etag. */

        if (!tar_pull_is_done(i))
                return;

        if (i->signature_job && i->checksum_job->style == VERIFICATION_PER_DIRECTORY && i->signature_job->error != 0) {
                log_error_errno(j->error, "Failed to retrieve signature file, cannot verify. (Try --verify=no?)");

                r = i->signature_job->error;
                goto finish;
        }

        i->tar_job->disk_fd = safe_close(i->tar_job->disk_fd);
        if (i->settings_job)
                i->settings_job->disk_fd = safe_close(i->settings_job->disk_fd);

        r = tar_pull_determine_path(i, NULL, &i->final_path);
        if (r < 0)
                goto finish;

        if (i->tar_pid > 0) {
                r = wait_for_terminate_and_check("tar", i->tar_pid, WAIT_LOG);
                i->tar_pid = 0;
                if (r < 0)
                        goto finish;
                if (r != EXIT_SUCCESS) {
                        r = -EIO;
                        goto finish;
                }
        }

        if (!i->tar_job->etag_exists) {
                /* This is a new download, verify it, and move it into place */

                tar_pull_report_progress(i, TAR_VERIFYING);

                r = pull_verify(i->tar_job, NULL, i->settings_job, i->checksum_job, i->signature_job);
                if (r < 0)
                        goto finish;

                tar_pull_report_progress(i, TAR_FINALIZING);

                r = import_make_read_only(i->temp_path);
                if (r < 0)
                        goto finish;

                r = rename_noreplace(AT_FDCWD, i->temp_path, AT_FDCWD, i->final_path);
                if (r < 0) {
                        log_error_errno(r, "Failed to rename to final image name to %s: %m", i->final_path);
                        goto finish;
                }

                i->temp_path = mfree(i->temp_path);

                if (i->settings_job &&
                    i->settings_job->error == 0) {

                        /* Also move the settings file into place, if it exists. Note that we do so only if we also
                         * moved the tar file in place, to keep things strictly in sync. */
                        assert(i->settings_temp_path);

                        /* Regenerate final name for this auxiliary file, we might know the etag of the file now, and
                         * we should incorporate it in the file name if we can */
                        i->settings_path = mfree(i->settings_path);

                        r = tar_pull_determine_path(i, ".nspawn", &i->settings_path);
                        if (r < 0)
                                goto finish;

                        r = import_make_read_only(i->settings_temp_path);
                        if (r < 0)
                                goto finish;

                        r = rename_noreplace(AT_FDCWD, i->settings_temp_path, AT_FDCWD, i->settings_path);
                        if (r < 0) {
                                log_error_errno(r, "Failed to rename settings file to %s: %m", i->settings_path);
                                goto finish;
                        }

                        i->settings_temp_path = mfree(i->settings_temp_path);
                }
        }

        tar_pull_report_progress(i, TAR_COPYING);

        r = tar_pull_make_local_copy(i);
        if (r < 0)
                goto finish;

        r = 0;

finish:
        if (i->on_finished)
                i->on_finished(i, r, i->userdata);
        else
                sd_event_exit(i->event, r);
}