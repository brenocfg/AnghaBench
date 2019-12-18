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
struct msg {int dummy; } ;
struct context {int dummy; } ;
struct conn {int send_ready; struct msg* (* send_next ) (struct context*,struct conn*) ;int /*<<< orphan*/  send_active; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ NC_OK ; 
 scalar_t__ msg_send_chain (struct context*,struct conn*,struct msg*) ; 
 struct msg* stub1 (struct context*,struct conn*) ; 

rstatus_t
msg_send(struct context *ctx, struct conn *conn)
{
    rstatus_t status;
    struct msg *msg;

    ASSERT(conn->send_active);

    conn->send_ready = 1;
    do {
        msg = conn->send_next(ctx, conn);
        if (msg == NULL) {
            /* nothing to send */
            return NC_OK;
        }

        status = msg_send_chain(ctx, conn, msg);
        if (status != NC_OK) {
            return status;
        }

    } while (conn->send_ready);

    return NC_OK;
}