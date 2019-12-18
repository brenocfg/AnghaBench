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
struct TYPE_6__ {scalar_t__ local; scalar_t__ image_root; scalar_t__ settings_path; scalar_t__ roothash_path; scalar_t__ final_path; scalar_t__ settings_temp_path; scalar_t__ roothash_temp_path; scalar_t__ temp_path; int /*<<< orphan*/  event; int /*<<< orphan*/  glue; int /*<<< orphan*/  signature_job; int /*<<< orphan*/  checksum_job; int /*<<< orphan*/  roothash_job; int /*<<< orphan*/  settings_job; int /*<<< orphan*/  raw_job; } ;
typedef  TYPE_1__ RawPull ;

/* Variables and functions */
 int /*<<< orphan*/  curl_glue_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pull_job_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

RawPull* raw_pull_unref(RawPull *i) {
        if (!i)
                return NULL;

        pull_job_unref(i->raw_job);
        pull_job_unref(i->settings_job);
        pull_job_unref(i->roothash_job);
        pull_job_unref(i->checksum_job);
        pull_job_unref(i->signature_job);

        curl_glue_unref(i->glue);
        sd_event_unref(i->event);

        if (i->temp_path) {
                (void) unlink(i->temp_path);
                free(i->temp_path);
        }

        if (i->roothash_temp_path) {
                (void) unlink(i->roothash_temp_path);
                free(i->roothash_temp_path);
        }

        if (i->settings_temp_path) {
                (void) unlink(i->settings_temp_path);
                free(i->settings_temp_path);
        }

        free(i->final_path);
        free(i->roothash_path);
        free(i->settings_path);
        free(i->image_root);
        free(i->local);
        return mfree(i);
}