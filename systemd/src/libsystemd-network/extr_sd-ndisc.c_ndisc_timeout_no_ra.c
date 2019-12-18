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
struct TYPE_6__ {int /*<<< orphan*/  timeout_no_ra; } ;
typedef  TYPE_1__ sd_ndisc ;
typedef  TYPE_1__ sd_event_source ;

/* Variables and functions */
 int /*<<< orphan*/  SD_NDISC_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  event_source_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_ndisc (char*) ; 
 int /*<<< orphan*/  ndisc_callback (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ndisc_timeout_no_ra(sd_event_source *s, uint64_t usec, void *userdata) {
        sd_ndisc *nd = userdata;

        assert(s);
        assert(nd);

        log_ndisc("No RA received before link confirmation timeout");

        (void) event_source_disable(nd->timeout_no_ra);
        ndisc_callback(nd, SD_NDISC_EVENT_TIMEOUT, NULL);

        return 0;
}