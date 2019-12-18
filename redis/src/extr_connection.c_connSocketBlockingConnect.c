#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fd; void* state; int /*<<< orphan*/  last_errno; } ;
typedef  TYPE_1__ connection ;

/* Variables and functions */
 int AE_WRITABLE ; 
 void* CONN_STATE_CONNECTED ; 
 void* CONN_STATE_ERROR ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int aeWait (int,int,long long) ; 
 int anetTcpNonBlockConnect (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int connSocketBlockingConnect(connection *conn, const char *addr, int port, long long timeout) {
    int fd = anetTcpNonBlockConnect(NULL,addr,port);
    if (fd == -1) {
        conn->state = CONN_STATE_ERROR;
        conn->last_errno = errno;
        return C_ERR;
    }

    if ((aeWait(fd, AE_WRITABLE, timeout) & AE_WRITABLE) == 0) {
        conn->state = CONN_STATE_ERROR;
        conn->last_errno = ETIMEDOUT;
    }

    conn->fd = fd;
    conn->state = CONN_STATE_CONNECTED;
    return C_OK;
}