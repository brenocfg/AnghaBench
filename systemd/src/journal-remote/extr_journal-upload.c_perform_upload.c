#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  current_cursor; int /*<<< orphan*/  last_cursor; int /*<<< orphan*/  answer; int /*<<< orphan*/  url; int /*<<< orphan*/  easy; scalar_t__* error; int /*<<< orphan*/  watchdog_timestamp; } ;
typedef  TYPE_1__ Uploader ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CURLINFO_RESPONSE_CODE ; 
 int EIO ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ curl_easy_getinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*) ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  free_and_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int,...) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strna (int /*<<< orphan*/ ) ; 
 int update_cursor_state (TYPE_1__*) ; 

__attribute__((used)) static int perform_upload(Uploader *u) {
        CURLcode code;
        long status;

        assert(u);

        u->watchdog_timestamp = now(CLOCK_MONOTONIC);
        code = curl_easy_perform(u->easy);
        if (code) {
                if (u->error[0])
                        log_error("Upload to %s failed: %.*s",
                                  u->url, (int) sizeof(u->error), u->error);
                else
                        log_error("Upload to %s failed: %s",
                                  u->url, curl_easy_strerror(code));
                return -EIO;
        }

        code = curl_easy_getinfo(u->easy, CURLINFO_RESPONSE_CODE, &status);
        if (code)
                return log_error_errno(SYNTHETIC_ERRNO(EUCLEAN),
                                       "Failed to retrieve response code: %s",
                                       curl_easy_strerror(code));

        if (status >= 300)
                return log_error_errno(SYNTHETIC_ERRNO(EIO),
                                       "Upload to %s failed with code %ld: %s",
                                       u->url, status, strna(u->answer));
        else if (status < 200)
                return log_error_errno(SYNTHETIC_ERRNO(EIO),
                                       "Upload to %s finished with unexpected code %ld: %s",
                                       u->url, status, strna(u->answer));
        else
                log_debug("Upload finished successfully with code %ld: %s",
                          status, strna(u->answer));

        free_and_replace(u->last_cursor, u->current_cursor);

        return update_cursor_state(u);
}