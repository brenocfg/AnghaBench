#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SyscallFilterSet ;

/* Variables and functions */
 unsigned int _SYSCALL_FILTER_SET_MAX ; 
 scalar_t__ isempty (char const*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__ const* syscall_filter_sets ; 

const SyscallFilterSet *syscall_filter_set_find(const char *name) {
        unsigned i;

        if (isempty(name) || name[0] != '@')
                return NULL;

        for (i = 0; i < _SYSCALL_FILTER_SET_MAX; i++)
                if (streq(syscall_filter_sets[i].name, name))
                        return syscall_filter_sets + i;

        return NULL;
}