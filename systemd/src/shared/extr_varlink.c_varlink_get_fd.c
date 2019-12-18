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
struct TYPE_4__ {scalar_t__ state; scalar_t__ fd; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ VARLINK_DISCONNECTED ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int varlink_get_fd(Varlink *v) {

        assert_return(v, -EINVAL);

        if (v->state == VARLINK_DISCONNECTED)
                return -ENOTCONN;
        if (v->fd < 0)
                return -EBADF;

        return v->fd;
}