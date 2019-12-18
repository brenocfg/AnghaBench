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
 int ENOMEM ; 
 scalar_t__ ctx ; 
 int /*<<< orphan*/  kmod_load_resources (scalar_t__) ; 
 scalar_t__ kmod_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmod_set_log_fn (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  udev_kmod_log ; 

__attribute__((used)) static int builtin_kmod_init(void) {
        if (ctx)
                return 0;

        ctx = kmod_new(NULL, NULL);
        if (!ctx)
                return -ENOMEM;

        log_debug("Load module index");
        kmod_set_log_fn(ctx, udev_kmod_log, NULL);
        kmod_load_resources(ctx);
        return 0;
}