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
struct TYPE_4__ {int class; int /*<<< orphan*/  leader; } ;
typedef  TYPE_1__ Machine ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  MACHINE_CONTAINER 129 
#define  MACHINE_HOST 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int openpt_allocate (int,char**) ; 
 int openpt_allocate_in_namespace (int /*<<< orphan*/ ,int,char**) ; 

int machine_openpt(Machine *m, int flags, char **ret_slave) {
        assert(m);

        switch (m->class) {

        case MACHINE_HOST:

                return openpt_allocate(flags, ret_slave);

        case MACHINE_CONTAINER:
                if (m->leader <= 0)
                        return -EINVAL;

                return openpt_allocate_in_namespace(m->leader, flags, ret_slave);

        default:
                return -EOPNOTSUPP;
        }
}