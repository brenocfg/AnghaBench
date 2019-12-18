#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_event ;
typedef  int /*<<< orphan*/  RawPull ;

/* Variables and functions */
 int /*<<< orphan*/  abs (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_raw_finished(RawPull *pull, int error, void *userdata) {
        sd_event *event = userdata;
        assert(pull);

        if (error == 0)
                log_info("Operation completed successfully.");

        sd_event_exit(event, abs(error));
}