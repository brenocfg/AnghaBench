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
struct conn {scalar_t__ (* recv ) (struct context*,struct conn*) ;int /*<<< orphan*/  sd; scalar_t__ proxy; scalar_t__ client; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct context*,struct conn*) ; 

__attribute__((used)) static rstatus_t
core_recv(struct context *ctx, struct conn *conn)
{
    rstatus_t status;

    status = conn->recv(ctx, conn);
    if (status != NC_OK) {
        log_debug(LOG_INFO, "recv on %c %d failed: %s",
                  conn->client ? 'c' : (conn->proxy ? 'p' : 's'), conn->sd,
                  strerror(errno));
    }

    return status;
}