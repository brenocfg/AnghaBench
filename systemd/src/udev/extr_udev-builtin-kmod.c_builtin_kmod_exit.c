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
 int /*<<< orphan*/  kmod_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static void builtin_kmod_exit(void) {
        log_debug("Unload module index");
        ctx = kmod_unref(ctx);
}