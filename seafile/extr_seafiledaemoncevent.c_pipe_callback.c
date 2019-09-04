#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gconstpointer ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
struct TYPE_8__ {scalar_t__ id; } ;
struct TYPE_7__ {int /*<<< orphan*/  handler_table; } ;
struct TYPE_6__ {int /*<<< orphan*/  handler_data; int /*<<< orphan*/  (* handler ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Handler ;
typedef  TYPE_2__ CEventManager ;
typedef  TYPE_3__ CEvent ;

/* Variables and functions */
 int CEVENT_SIZE ; 
 TYPE_1__* g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,scalar_t__) ; 
 int seaf_pipe_readn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void pipe_callback (evutil_socket_t fd, short event, void *vmgr)
{
    CEventManager *manager = (CEventManager *) vmgr;
    CEvent *cevent;
    char buf[CEVENT_SIZE];
    
    if (seaf_pipe_readn(fd, buf, CEVENT_SIZE) != CEVENT_SIZE) {
        return;
    }

    cevent = (CEvent *)buf;
    Handler *h = g_hash_table_lookup (manager->handler_table,
                                      (gconstpointer)(long)cevent->id);
    if (h == NULL) {
        g_warning ("no handler for event type %d\n", cevent->id);
        return;
    }

    h->handler(cevent, h->handler_data);
}