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

/* Variables and functions */
 scalar_t__ ctx ; 
 int link_config_ctx_new (scalar_t__*) ; 
 int link_config_load (scalar_t__) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int builtin_net_setup_link_init(void) {
        int r;

        if (ctx)
                return 0;

        r = link_config_ctx_new(&ctx);
        if (r < 0)
                return r;

        r = link_config_load(ctx);
        if (r < 0)
                return r;

        log_debug("Created link configuration context.");
        return 0;
}