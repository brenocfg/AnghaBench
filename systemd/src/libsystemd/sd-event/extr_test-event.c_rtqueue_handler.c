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
struct signalfd_siginfo {int /*<<< orphan*/  ssi_int; } ;
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 int /*<<< orphan*/  last_rtqueue_sigval ; 
 int /*<<< orphan*/  n_rtqueue ; 

__attribute__((used)) static int rtqueue_handler(sd_event_source *s, const struct signalfd_siginfo *si, void *userdata) {
        last_rtqueue_sigval = si->ssi_int;
        n_rtqueue++;
        return 0;
}