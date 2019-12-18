#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rtnl; int /*<<< orphan*/  ethtool_fd; } ;
typedef  TYPE_1__ link_config_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  link_configs_free (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_unref (int /*<<< orphan*/ ) ; 

void link_config_ctx_free(link_config_ctx *ctx) {
        if (!ctx)
                return;

        safe_close(ctx->ethtool_fd);

        sd_netlink_unref(ctx->rtnl);

        link_configs_free(ctx);

        free(ctx);

        return;
}