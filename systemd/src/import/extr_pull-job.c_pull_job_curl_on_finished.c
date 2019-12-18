#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct timespec {int dummy; } ;
struct TYPE_4__ {scalar_t__ state; int etag_exists; scalar_t__ style; scalar_t__ content_length; scalar_t__ written_compressed; scalar_t__ disk_fd; scalar_t__ mtime; scalar_t__ url; scalar_t__ etag; int /*<<< orphan*/  written_uncompressed; scalar_t__ allow_sparse; int /*<<< orphan*/  checksum; scalar_t__ checksum_context; int /*<<< orphan*/ * curl; } ;
typedef  TYPE_1__ PullJob ;
typedef  int /*<<< orphan*/  CurlGlue ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_PRIVATE ; 
 int /*<<< orphan*/  CURLINFO_RESPONSE_CODE ; 
 int EIO ; 
 int /*<<< orphan*/  GCRY_MD_SHA256 ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PULL_JOB_DONE ; 
 int /*<<< orphan*/  PULL_JOB_FAILED ; 
 scalar_t__ PULL_JOB_RUNNING ; 
 scalar_t__ VERIFICATION_PER_DIRECTORY ; 
 scalar_t__ VERIFICATION_PER_FILE ; 
 scalar_t__ curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fd_setcrtime (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fsetxattr (scalar_t__,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftruncate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futimens (scalar_t__,struct timespec*) ; 
 int /*<<< orphan*/  gcry_md_get_algo_dlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gcry_md_read (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexmem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (char*,...) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  pull_job_finish (TYPE_1__*,int) ; 
 int pull_job_restart (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  timespec_store (struct timespec*,scalar_t__) ; 

void pull_job_curl_on_finished(CurlGlue *g, CURL *curl, CURLcode result) {
        PullJob *j = NULL;
        CURLcode code;
        long status;
        int r;

        if (curl_easy_getinfo(curl, CURLINFO_PRIVATE, (char **)&j) != CURLE_OK)
                return;

        if (!j || IN_SET(j->state, PULL_JOB_DONE, PULL_JOB_FAILED))
                return;

        if (result != CURLE_OK) {
                log_error("Transfer failed: %s", curl_easy_strerror(result));
                r = -EIO;
                goto finish;
        }

        code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
        if (code != CURLE_OK) {
                log_error("Failed to retrieve response code: %s", curl_easy_strerror(code));
                r = -EIO;
                goto finish;
        } else if (status == 304) {
                log_info("Image already downloaded. Skipping download.");
                j->etag_exists = true;
                r = 0;
                goto finish;
        } else if (status >= 300) {
                if (status == 404 && j->style == VERIFICATION_PER_FILE) {

                        /* retry pull job with SHA256SUMS file */
                        r = pull_job_restart(j);
                        if (r < 0)
                                goto finish;

                        code = curl_easy_getinfo(j->curl, CURLINFO_RESPONSE_CODE, &status);
                        if (code != CURLE_OK) {
                                log_error("Failed to retrieve response code: %s", curl_easy_strerror(code));
                                r = -EIO;
                                goto finish;
                        }

                        if (status == 0) {
                                j->style = VERIFICATION_PER_DIRECTORY;
                                return;
                        }
                }

                log_error("HTTP request to %s failed with code %li.", j->url, status);
                r = -EIO;
                goto finish;
        } else if (status < 200) {
                log_error("HTTP request to %s finished with unexpected code %li.", j->url, status);
                r = -EIO;
                goto finish;
        }

        if (j->state != PULL_JOB_RUNNING) {
                log_error("Premature connection termination.");
                r = -EIO;
                goto finish;
        }

        if (j->content_length != (uint64_t) -1 &&
            j->content_length != j->written_compressed) {
                log_error("Download truncated.");
                r = -EIO;
                goto finish;
        }

        if (j->checksum_context) {
                uint8_t *k;

                k = gcry_md_read(j->checksum_context, GCRY_MD_SHA256);
                if (!k) {
                        log_error("Failed to get checksum.");
                        r = -EIO;
                        goto finish;
                }

                j->checksum = hexmem(k, gcry_md_get_algo_dlen(GCRY_MD_SHA256));
                if (!j->checksum) {
                        r = log_oom();
                        goto finish;
                }

                log_debug("SHA256 of %s is %s.", j->url, j->checksum);
        }

        if (j->disk_fd >= 0 && j->allow_sparse) {
                /* Make sure the file size is right, in case the file was
                 * sparse and we just seeked for the last part */

                if (ftruncate(j->disk_fd, j->written_uncompressed) < 0) {
                        r = log_error_errno(errno, "Failed to truncate file: %m");
                        goto finish;
                }

                if (j->etag)
                        (void) fsetxattr(j->disk_fd, "user.source_etag", j->etag, strlen(j->etag), 0);
                if (j->url)
                        (void) fsetxattr(j->disk_fd, "user.source_url", j->url, strlen(j->url), 0);

                if (j->mtime != 0) {
                        struct timespec ut[2];

                        timespec_store(&ut[0], j->mtime);
                        ut[1] = ut[0];
                        (void) futimens(j->disk_fd, ut);

                        (void) fd_setcrtime(j->disk_fd, j->mtime);
                }
        }

        r = 0;

finish:
        pull_job_finish(j, r);
}