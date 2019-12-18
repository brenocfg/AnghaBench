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
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  varlink_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  varlink_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int quit_callback(sd_event_source *event, void *userdata) {
        Varlink *v = userdata;

        assert(event);
        assert(v);

        varlink_flush(v);
        varlink_close(v);

        return 1;
}