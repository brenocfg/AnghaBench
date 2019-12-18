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
typedef  scalar_t__ usec_t ;
struct TYPE_4__ {scalar_t__ state; scalar_t__ timeout; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USEC_INFINITY ; 
 int /*<<< orphan*/  VARLINK_AWAITING_REPLY ; 
 int /*<<< orphan*/  VARLINK_CALLING ; 
 scalar_t__ VARLINK_DISCONNECTED ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ usec_add (int /*<<< orphan*/ ,scalar_t__) ; 

int varlink_get_timeout(Varlink *v, usec_t *ret) {
        assert_return(v, -EINVAL);

        if (v->state == VARLINK_DISCONNECTED)
                return -ENOTCONN;

        if (IN_SET(v->state, VARLINK_AWAITING_REPLY, VARLINK_CALLING) &&
            v->timeout != USEC_INFINITY) {
                if (ret)
                        *ret = usec_add(v->timestamp, v->timeout);
                return 1;
        } else {
                if (ret)
                        *ret = USEC_INFINITY;
                return 0;
        }
}