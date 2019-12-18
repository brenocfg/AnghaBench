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
struct TYPE_2__ {char* name; char* help; } ;

/* Variables and functions */
 unsigned int _UDEV_BUILTIN_MAX ; 
 TYPE_1__** builtins ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void udev_builtin_list(void) {
        unsigned i;

        for (i = 0; i < _UDEV_BUILTIN_MAX; i++)
                if (builtins[i])
                        fprintf(stderr, "  %-14s  %s\n", builtins[i]->name, builtins[i]->help);
}