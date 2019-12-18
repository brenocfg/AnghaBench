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
struct context {int dummy; } ;
struct conn {int /*<<< orphan*/  err; int /*<<< orphan*/  sd; scalar_t__ proxy; scalar_t__ client; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  core_close (struct context*,struct conn*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_warn (char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nc_get_soerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
core_error(struct context *ctx, struct conn *conn)
{
    rstatus_t status;
    char type = conn->client ? 'c' : (conn->proxy ? 'p' : 's');

    status = nc_get_soerror(conn->sd);
    if (status < 0) {
        log_warn("get soerr on %c %d failed, ignored: %s", type, conn->sd,
                  strerror(errno));
    }
    conn->err = errno;

    core_close(ctx, conn);
}