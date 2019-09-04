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
struct server_pool {int server_connections; int /*<<< orphan*/  server; } ;
struct context {int max_nsconn; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_OK ; 
 int array_n (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rstatus_t
server_pool_each_calc_connections(void *elem, void *data)
{
    struct server_pool *sp = elem;
    struct context *ctx = data;

    ctx->max_nsconn += sp->server_connections * array_n(&sp->server);
    ctx->max_nsconn += 1; /* pool listening socket */

    return NC_OK;
}