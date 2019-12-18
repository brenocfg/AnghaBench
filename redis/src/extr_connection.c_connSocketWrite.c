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
struct TYPE_3__ {int /*<<< orphan*/  state; scalar_t__ last_errno; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ connection ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_STATE_ERROR ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ errno ; 
 int write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int connSocketWrite(connection *conn, const void *data, size_t data_len) {
    int ret = write(conn->fd, data, data_len);
    if (ret < 0 && errno != EAGAIN) {
        conn->last_errno = errno;
        conn->state = CONN_STATE_ERROR;
    }

    return ret;
}