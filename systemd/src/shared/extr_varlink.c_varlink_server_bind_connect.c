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
struct TYPE_4__ {scalar_t__ connect_callback; } ;
typedef  TYPE_1__ VarlinkServer ;
typedef  scalar_t__ VarlinkConnect ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int varlink_server_bind_connect(VarlinkServer *s, VarlinkConnect callback) {
        assert_return(s, -EINVAL);

        if (callback && s->connect_callback && callback != s->connect_callback)
                return -EBUSY;

        s->connect_callback = callback;
        return 0;
}