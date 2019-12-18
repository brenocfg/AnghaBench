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
typedef  size_t UdevBuiltinCommand ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 size_t _UDEV_BUILTIN_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** builtins ; 

const char *udev_builtin_name(UdevBuiltinCommand cmd) {
        assert(cmd >= 0 && cmd < _UDEV_BUILTIN_MAX);

        if (!builtins[cmd])
                return NULL;

        return builtins[cmd]->name;
}