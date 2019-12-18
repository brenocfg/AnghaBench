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
struct TYPE_4__ {void* userdata; } ;
typedef  TYPE_1__ VarlinkServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ *) ; 

void* varlink_server_set_userdata(VarlinkServer *s, void *userdata) {
        void *ret;

        assert_return(s, NULL);

        ret = s->userdata;
        s->userdata = userdata;

        return ret;
}