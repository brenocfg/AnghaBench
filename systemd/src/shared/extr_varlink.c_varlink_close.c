#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ state; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ VARLINK_DISCONNECTED ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varlink_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_detach_server (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_set_state (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  varlink_unref (TYPE_1__*) ; 

int varlink_close(Varlink *v) {

        assert_return(v, -EINVAL);

        if (v->state == VARLINK_DISCONNECTED)
                return 0;

        varlink_set_state(v, VARLINK_DISCONNECTED);

        /* Let's take a reference first, since varlink_detach_server() might drop the final (dangling) ref
         * which would destroy us before we can call varlink_clear() */
        varlink_ref(v);
        varlink_detach_server(v);
        varlink_clear(v);
        varlink_unref(v);

        return 1;
}