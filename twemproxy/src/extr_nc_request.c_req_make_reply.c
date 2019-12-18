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
struct msg {int done; scalar_t__ request; struct msg* peer; } ;
struct context {int dummy; } ;
struct conn {int /*<<< orphan*/  (* enqueue_outq ) (struct context*,struct conn*,struct msg*) ;int /*<<< orphan*/  err; int /*<<< orphan*/  redis; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/  errno ; 
 struct msg* msg_get (struct conn*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct context*,struct conn*,struct msg*) ; 

__attribute__((used)) static rstatus_t
req_make_reply(struct context *ctx, struct conn *conn, struct msg *req)
{
    struct msg *rsp;

    rsp = msg_get(conn, false, conn->redis); /* replay */
    if (rsp == NULL) {
        conn->err = errno;
        return NC_ENOMEM;
    }

    req->peer = rsp;
    rsp->peer = req;
    rsp->request = 0;

    req->done = 1;
    conn->enqueue_outq(ctx, conn, req);

    return NC_OK;
}