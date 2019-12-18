#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msg {int request; struct msg* peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  msg_put (struct msg*) ; 
 int /*<<< orphan*/  msg_tmo_delete (struct msg*) ; 
 int /*<<< orphan*/  req_log (struct msg*) ; 
 int /*<<< orphan*/  rsp_put (struct msg*) ; 

void
req_put(struct msg *msg)
{
    struct msg *pmsg; /* peer message (response) */

    ASSERT(msg->request);

    req_log(msg);

    pmsg = msg->peer;
    if (pmsg != NULL) {
        ASSERT(!pmsg->request && pmsg->peer == msg);
        msg->peer = NULL;
        pmsg->peer = NULL;
        rsp_put(pmsg);
    }

    msg_tmo_delete(msg);

    msg_put(msg);
}