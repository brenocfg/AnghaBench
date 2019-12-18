#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* module; } ;
typedef  TYPE_1__ vlc_plugin_t ;
typedef  int /*<<< orphan*/  vlc_plugin_cb ;
struct TYPE_5__ {void* pf_activate; void* deactivate; int /*<<< orphan*/  deactivate_name; int /*<<< orphan*/  activate_name; struct TYPE_5__* next; } ;
typedef  TYPE_2__ module_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_plugin_free_symbols (void*) ; 
 scalar_t__ vlc_plugin_get_symbol (void*,int /*<<< orphan*/ ,void**) ; 
 void* vlc_plugin_get_symbols (int /*<<< orphan*/ ) ; 

int vlc_plugin_resolve(vlc_plugin_t *plugin, vlc_plugin_cb entry)
{
    void *syms = vlc_plugin_get_symbols(entry);
    int ret = 0;

    /* Resolve modules activate/deactivate callbacks */
    for (module_t *module = plugin->module;
         module != NULL;
         module = module->next)
    {
        void *deactivate;

        if (vlc_plugin_get_symbol(syms, module->activate_name,
                                  &module->pf_activate)
         || vlc_plugin_get_symbol(syms, module->deactivate_name, &deactivate))
        {
            ret = -1;
            break;
        }

        module->deactivate = deactivate;
    }

    vlc_plugin_free_symbols(syms);
    return ret;
}