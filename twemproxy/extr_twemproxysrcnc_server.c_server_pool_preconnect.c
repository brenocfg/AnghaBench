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
struct context {int /*<<< orphan*/  pool; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 scalar_t__ array_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_pool_each_preconnect ; 

rstatus_t
server_pool_preconnect(struct context *ctx)
{
    rstatus_t status;

    status = array_each(&ctx->pool, server_pool_each_preconnect, NULL);
    if (status != NC_OK) {
        return status;
    }

    return NC_OK;
}