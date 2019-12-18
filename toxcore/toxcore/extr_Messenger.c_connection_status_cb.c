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
struct TYPE_4__ {unsigned int last_connection_status; int /*<<< orphan*/  core_connection_change_userdata; int /*<<< orphan*/  (* core_connection_change ) (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  onion_c; } ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 unsigned int onion_connection_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connection_status_cb(Messenger *m)
{
    unsigned int conn_status = onion_connection_status(m->onion_c);

    if (conn_status != m->last_connection_status) {
        if (m->core_connection_change)
            (*m->core_connection_change)(m, conn_status, m->core_connection_change_userdata);

        m->last_connection_status = conn_status;
    }
}