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
struct TYPE_6__ {int /*<<< orphan*/  checksum; int /*<<< orphan*/  payload; int /*<<< orphan*/  old_etags; int /*<<< orphan*/  etag; int /*<<< orphan*/  url; scalar_t__ checksum_context; int /*<<< orphan*/  compress; int /*<<< orphan*/  disk_fd; int /*<<< orphan*/  request_header; int /*<<< orphan*/  curl; int /*<<< orphan*/  glue; } ;
typedef  TYPE_1__ PullJob ;

/* Variables and functions */
 int /*<<< orphan*/  curl_glue_remove_and_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_close (scalar_t__) ; 
 int /*<<< orphan*/  import_compress_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

PullJob* pull_job_unref(PullJob *j) {
        if (!j)
                return NULL;

        curl_glue_remove_and_free(j->glue, j->curl);
        curl_slist_free_all(j->request_header);

        safe_close(j->disk_fd);

        import_compress_free(&j->compress);

        if (j->checksum_context)
                gcry_md_close(j->checksum_context);

        free(j->url);
        free(j->etag);
        strv_free(j->old_etags);
        free(j->payload);
        free(j->checksum);

        return mfree(j);
}