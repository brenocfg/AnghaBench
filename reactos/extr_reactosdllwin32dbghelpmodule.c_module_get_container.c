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
struct process {struct module const* lmodules; } ;
struct TYPE_2__ {scalar_t__ BaseOfImage; scalar_t__ ImageSize; } ;
typedef  struct module {TYPE_1__ module; struct module const* next; } const module ;

/* Variables and functions */

__attribute__((used)) static struct module* module_get_container(const struct process* pcs,
                                    const struct module* inner)
{
    struct module*      module;
     
    for (module = pcs->lmodules; module; module = module->next)
    {
        if (module != inner &&
            module->module.BaseOfImage <= inner->module.BaseOfImage &&
            module->module.BaseOfImage + module->module.ImageSize >=
            inner->module.BaseOfImage + inner->module.ImageSize)
            return module;
    }
    return NULL;
}