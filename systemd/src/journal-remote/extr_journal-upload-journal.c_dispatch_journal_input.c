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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_4__ {scalar_t__ uploading; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int check_journal_input (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int dispatch_journal_input(sd_event_source *event,
                                  int fd,
                                  uint32_t revents,
                                  void *userp) {
        Uploader *u = userp;

        assert(u);

        if (u->uploading)
                return 0;

        log_debug("Detected journal input, checking for new data.");
        return check_journal_input(u);
}