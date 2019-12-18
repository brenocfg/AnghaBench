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
typedef  int usec_t ;
struct TYPE_6__ {scalar_t__ timer; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ CurlGlue ;
typedef  TYPE_1__ CURLM ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_OFF ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int /*<<< orphan*/  curl_glue_on_timer ; 
 int now (int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (scalar_t__,char*) ; 
 scalar_t__ sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_source_set_time (scalar_t__,int) ; 

__attribute__((used)) static int curl_glue_timer_callback(CURLM *curl, long timeout_ms, void *userdata) {
        CurlGlue *g = userdata;
        usec_t usec;

        assert(curl);
        assert(g);

        if (timeout_ms < 0) {
                if (g->timer) {
                        if (sd_event_source_set_enabled(g->timer, SD_EVENT_OFF) < 0)
                                return -1;
                }

                return 0;
        }

        usec = now(clock_boottime_or_monotonic()) + (usec_t) timeout_ms * USEC_PER_MSEC + USEC_PER_MSEC - 1;

        if (g->timer) {
                if (sd_event_source_set_time(g->timer, usec) < 0)
                        return -1;

                if (sd_event_source_set_enabled(g->timer, SD_EVENT_ONESHOT) < 0)
                        return -1;
        } else {
                if (sd_event_add_time(g->event, &g->timer, clock_boottime_or_monotonic(), usec, 0, curl_glue_on_timer, g) < 0)
                        return -1;

                (void) sd_event_source_set_description(g->timer, "curl-timer");
        }

        return 0;
}