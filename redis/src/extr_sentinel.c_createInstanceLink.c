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
struct TYPE_4__ {int refcount; int disconnected; void* last_pong_time; void* last_avail_time; scalar_t__ last_ping_time; void* act_ping_time; scalar_t__ pc_last_activity; scalar_t__ last_reconn_time; scalar_t__ pc_conn_time; scalar_t__ cc_conn_time; int /*<<< orphan*/ * pc; int /*<<< orphan*/ * cc; scalar_t__ pending_commands; } ;
typedef  TYPE_1__ instanceLink ;

/* Variables and functions */
 void* mstime () ; 
 TYPE_1__* zmalloc (int) ; 

instanceLink *createInstanceLink(void) {
    instanceLink *link = zmalloc(sizeof(*link));

    link->refcount = 1;
    link->disconnected = 1;
    link->pending_commands = 0;
    link->cc = NULL;
    link->pc = NULL;
    link->cc_conn_time = 0;
    link->pc_conn_time = 0;
    link->last_reconn_time = 0;
    link->pc_last_activity = 0;
    /* We set the act_ping_time to "now" even if we actually don't have yet
     * a connection with the node, nor we sent a ping.
     * This is useful to detect a timeout in case we'll not be able to connect
     * with the node at all. */
    link->act_ping_time = mstime();
    link->last_ping_time = 0;
    link->last_avail_time = mstime();
    link->last_pong_time = mstime();
    return link;
}