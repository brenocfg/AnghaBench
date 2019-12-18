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
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ *) ; 

void* varlink_set_userdata(Varlink *v, void *userdata) {
        void *old;

        assert_return(v, NULL);

        old = v->userdata;
        v->userdata = userdata;

        return old;
}