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
struct msg {int result; int /*<<< orphan*/  (* parser ) (struct msg*) ;} ;
struct context {int dummy; } ;
struct conn {scalar_t__ err; int /*<<< orphan*/  (* recv_done ) (struct context*,struct conn*,struct msg*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
#define  MSG_PARSE_AGAIN 130 
#define  MSG_PARSE_OK 129 
#define  MSG_PARSE_REPAIR 128 
 int /*<<< orphan*/  NC_ERROR ; 
 int /*<<< orphan*/  NC_OK ; 
 scalar_t__ errno ; 
 scalar_t__ msg_empty (struct msg*) ; 
 int /*<<< orphan*/  msg_parsed (struct context*,struct conn*,struct msg*) ; 
 int /*<<< orphan*/  msg_repair (struct context*,struct conn*,struct msg*) ; 
 int /*<<< orphan*/  stub1 (struct context*,struct conn*,struct msg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct msg*) ; 

__attribute__((used)) static rstatus_t
msg_parse(struct context *ctx, struct conn *conn, struct msg *msg)
{
    rstatus_t status;

    if (msg_empty(msg)) {
        /* no data to parse */
        conn->recv_done(ctx, conn, msg, NULL);
        return NC_OK;
    }

    msg->parser(msg);

    switch (msg->result) {
    case MSG_PARSE_OK:
        status = msg_parsed(ctx, conn, msg);
        break;

    case MSG_PARSE_REPAIR:
        status = msg_repair(ctx, conn, msg);
        break;

    case MSG_PARSE_AGAIN:
        status = NC_OK;
        break;

    default:
        status = NC_ERROR;
        conn->err = errno;
        break;
    }

    return conn->err != 0 ? NC_ERROR : status;
}