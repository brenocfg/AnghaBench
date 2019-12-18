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
struct TYPE_4__ {struct TYPE_4__* pp_shortcuts; struct TYPE_4__* next; } ;
typedef  TYPE_1__ module_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void vlc_module_destroy (module_t *module)
{
    while (module != NULL)
    {
        module_t *next = module->next;

        free(module->pp_shortcuts);
        free(module);
        module = next;
    }
}