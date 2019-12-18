#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ state; scalar_t__ defer_event_source; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  SD_EVENT_OFF ; 
 int /*<<< orphan*/  SD_EVENT_ON ; 
 scalar_t__ VARLINK_DISCONNECTED ; 
 int /*<<< orphan*/  VARLINK_PENDING_DISCONNECT ; 
 scalar_t__ VARLINK_STATE_IS_ALIVE (scalar_t__) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varlink_close (TYPE_1__*) ; 
 int varlink_dispatch_disconnect (TYPE_1__*) ; 
 int varlink_dispatch_method (TYPE_1__*) ; 
 int varlink_dispatch_reply (TYPE_1__*) ; 
 int varlink_dispatch_timeout (TYPE_1__*) ; 
 int varlink_parse_message (TYPE_1__*) ; 
 int varlink_read (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int varlink_test_disconnect (TYPE_1__*) ; 
 int varlink_test_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_unref (TYPE_1__*) ; 
 int varlink_write (TYPE_1__*) ; 

int varlink_process(Varlink *v) {
        int r;

        assert_return(v, -EINVAL);

        if (v->state == VARLINK_DISCONNECTED)
                return -ENOTCONN;

        varlink_ref(v);

        r = varlink_write(v);
        if (r != 0)
                goto finish;

        r = varlink_dispatch_reply(v);
        if (r != 0)
                goto finish;

        r = varlink_dispatch_method(v);
        if (r != 0)
                goto finish;

        r = varlink_parse_message(v);
        if (r != 0)
                goto finish;

        r = varlink_read(v);
        if (r != 0)
                goto finish;

        r = varlink_test_disconnect(v);
        if (r != 0)
                goto finish;

        r = varlink_dispatch_disconnect(v);
        if (r != 0)
                goto finish;

        r = varlink_test_timeout(v);
        if (r != 0)
                goto finish;

        r = varlink_dispatch_timeout(v);
        if (r != 0)
                goto finish;

finish:
        if (r >= 0 && v->defer_event_source) {
                int q;

                /* If we did some processing, make sure we are called again soon */
                q = sd_event_source_set_enabled(v->defer_event_source, r > 0 ? SD_EVENT_ON : SD_EVENT_OFF);
                if (q < 0)
                        r = q;
        }

        if (r < 0) {
                if (VARLINK_STATE_IS_ALIVE(v->state))
                        /* Initiate disconnection */
                        varlink_set_state(v, VARLINK_PENDING_DISCONNECT);
                else
                        /* We failed while disconnecting, in that case close right away */
                        varlink_close(v);
        }

        varlink_unref(v);
        return r;
}