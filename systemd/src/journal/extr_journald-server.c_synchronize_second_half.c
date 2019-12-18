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
typedef  int /*<<< orphan*/  Server ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ *) ; 
 int log_error_errno (int,char*) ; 
 int sd_event_source_set_floating (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  server_full_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * varlink_get_userdata (int /*<<< orphan*/ *) ; 
 int varlink_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int synchronize_second_half(sd_event_source *event_source, void *userdata) {
        Varlink *link = userdata;
        Server *s;
        int r;

        assert(link);
        assert_se(s = varlink_get_userdata(link));

        /* This is the "second half" of the Synchronize() varlink method. This function is called as deferred
         * event source at a low priority to ensure the synchronization completes after all queued log
         * messages are processed. */
        server_full_sync(s);

        /* Let's get rid of the event source now, by marking it as non-floating again. It then has no ref
         * anymore and is immediately destroyed after we return from this function, i.e. from this event
         * source handler at the end. */
        r = sd_event_source_set_floating(event_source, false);
        if (r < 0)
                return log_error_errno(r, "Failed to mark event source as non-floating: %m");

        return varlink_reply(link, NULL);
}