#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  family; } ;
struct server {TYPE_1__ info; int /*<<< orphan*/  port; int /*<<< orphan*/  addrstr; } ;
struct conn {int done; struct sockaddr* addr; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  family; int /*<<< orphan*/  err; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHOSTDOWN ; 
 scalar_t__ NC_OK ; 
 scalar_t__ nc_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
server_resolve(struct server *server, struct conn *conn)
{
    rstatus_t status;

    status = nc_resolve(&server->addrstr, server->port, &server->info);
    if (status != NC_OK) {
        conn->err = EHOSTDOWN;
        conn->done = 1;
        return;
    }

    conn->family = server->info.family;
    conn->addrlen = server->info.addrlen;
    conn->addr = (struct sockaddr *)&server->info.addr;
}