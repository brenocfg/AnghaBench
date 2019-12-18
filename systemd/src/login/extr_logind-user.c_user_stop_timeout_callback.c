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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  User ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_add_to_gc_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int user_stop_timeout_callback(sd_event_source *es, uint64_t usec, void *userdata) {
        User *u = userdata;

        assert(u);
        user_add_to_gc_queue(u);

        return 0;
}