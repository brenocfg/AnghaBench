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
struct TYPE_7__ {int fd; TYPE_1__* type; int /*<<< orphan*/  conn_handler; int /*<<< orphan*/  state; int /*<<< orphan*/  last_errno; } ;
typedef  TYPE_2__ connection ;
struct TYPE_8__ {int /*<<< orphan*/  el; } ;
struct TYPE_6__ {int /*<<< orphan*/  ae_handler; } ;
typedef  int /*<<< orphan*/  ConnectionCallbackFunc ;

/* Variables and functions */
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/  CONN_STATE_CONNECTING ; 
 int /*<<< orphan*/  CONN_STATE_ERROR ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  aeCreateFileEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int anetTcpNonBlockBestEffortBindConnect (int /*<<< orphan*/ *,char const*,int,char const*) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_3__ server ; 

__attribute__((used)) static int connSocketConnect(connection *conn, const char *addr, int port, const char *src_addr,
        ConnectionCallbackFunc connect_handler) {
    int fd = anetTcpNonBlockBestEffortBindConnect(NULL,addr,port,src_addr);
    if (fd == -1) {
        conn->state = CONN_STATE_ERROR;
        conn->last_errno = errno;
        return C_ERR;
    }

    conn->fd = fd;
    conn->state = CONN_STATE_CONNECTING;

    conn->conn_handler = connect_handler;
    aeCreateFileEvent(server.el, conn->fd, AE_WRITABLE,
            conn->type->ae_handler, conn);

    return C_OK;
}