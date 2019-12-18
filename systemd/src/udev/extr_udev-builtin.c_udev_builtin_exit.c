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
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) () ;} ;

/* Variables and functions */
 unsigned int _UDEV_BUILTIN_MAX ; 
 TYPE_1__** builtins ; 
 int initialized ; 
 int /*<<< orphan*/  stub1 () ; 

void udev_builtin_exit(void) {
        unsigned i;

        if (!initialized)
                return;

        for (i = 0; i < _UDEV_BUILTIN_MAX; i++)
                if (builtins[i] && builtins[i]->exit)
                        builtins[i]->exit();

        initialized = false;
}