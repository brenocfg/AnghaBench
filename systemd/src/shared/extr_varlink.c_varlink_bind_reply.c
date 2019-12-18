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
typedef  scalar_t__ VarlinkReply ;
struct TYPE_4__ {scalar_t__ reply_callback; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int varlink_bind_reply(Varlink *v, VarlinkReply callback) {
        assert_return(v, -EINVAL);

        if (callback && v->reply_callback && callback != v->reply_callback)
                return -EBUSY;

        v->reply_callback = callback;

        return 0;
}