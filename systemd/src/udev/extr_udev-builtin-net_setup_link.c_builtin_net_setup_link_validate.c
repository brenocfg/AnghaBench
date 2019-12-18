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
 int /*<<< orphan*/  ctx ; 
 int link_config_should_reload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static bool builtin_net_setup_link_validate(void) {
        log_debug("Check if link configuration needs reloading.");
        if (!ctx)
                return false;

        return link_config_should_reload(ctx);
}