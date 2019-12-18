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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  curl; } ;
typedef  TYPE_1__ sd_event_source ;
typedef  TYPE_1__ CurlGlue ;

/* Variables and functions */
 scalar_t__ CURLM_OK ; 
 int /*<<< orphan*/  CURL_SOCKET_TIMEOUT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  curl_glue_check_finished (TYPE_1__*) ; 
 scalar_t__ curl_multi_socket_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int curl_glue_on_timer(sd_event_source *s, uint64_t usec, void *userdata) {
        CurlGlue *g = userdata;
        int k = 0;

        assert(s);
        assert(g);

        if (curl_multi_socket_action(g->curl, CURL_SOCKET_TIMEOUT, 0, &k) != CURLM_OK)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Failed to propagate timeout.");

        curl_glue_check_finished(g);
        return 0;
}