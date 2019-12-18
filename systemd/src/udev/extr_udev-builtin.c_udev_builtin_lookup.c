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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WHITESPACE ; 
 size_t _UDEV_BUILTIN_INVALID ; 
 size_t _UDEV_BUILTIN_MAX ; 
 int /*<<< orphan*/  assert (char const*) ; 
 TYPE_1__** builtins ; 
 size_t strcspn (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strneq (int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ strspn (char const*,int /*<<< orphan*/ ) ; 

UdevBuiltinCommand udev_builtin_lookup(const char *command) {
        UdevBuiltinCommand i;
        size_t n;

        assert(command);

        command += strspn(command, WHITESPACE);
        n = strcspn(command, WHITESPACE);
        for (i = 0; i < _UDEV_BUILTIN_MAX; i++)
                if (builtins[i] && strneq(builtins[i]->name, command, n))
                        return i;

        return _UDEV_BUILTIN_INVALID;
}