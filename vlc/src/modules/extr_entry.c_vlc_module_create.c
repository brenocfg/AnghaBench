#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  modules_count; TYPE_2__* module; } ;
typedef  TYPE_1__ vlc_plugin_t ;
struct TYPE_7__ {int i_score; int /*<<< orphan*/ * deactivate; int /*<<< orphan*/ * pf_activate; int /*<<< orphan*/ * deactivate_name; int /*<<< orphan*/ * activate_name; int /*<<< orphan*/ * psz_capability; scalar_t__ i_shortcuts; int /*<<< orphan*/ * pp_shortcuts; int /*<<< orphan*/ * psz_help; int /*<<< orphan*/ * psz_longname; int /*<<< orphan*/ * psz_shortname; TYPE_1__* plugin; struct TYPE_7__* next; } ;
typedef  TYPE_2__ module_t ;

/* Variables and functions */
 TYPE_2__* malloc (int) ; 

module_t *vlc_module_create(vlc_plugin_t *plugin)
{
    module_t *module = malloc (sizeof (*module));
    if (module == NULL)
        return NULL;

    /* NOTE XXX: For backward compatibility with preferences UIs, the first
     * module must stay first. That defines under which module, the
     * configuration items of the plugin belong. The order of the following
     * entries is irrelevant. */
    module_t *parent = plugin->module;
    if (parent == NULL)
    {
        module->next = NULL;
        plugin->module = module;
    }
    else
    {
        module->next = parent->next;
        parent->next = module;
    }

    plugin->modules_count++;
    module->plugin = plugin;

    module->psz_shortname = NULL;
    module->psz_longname = NULL;
    module->psz_help = NULL;
    module->pp_shortcuts = NULL;
    module->i_shortcuts = 0;
    module->psz_capability = NULL;
    module->i_score = (parent != NULL) ? parent->i_score : 1;
    module->activate_name = NULL;
    module->deactivate_name = NULL;
    module->pf_activate = NULL;
    module->deactivate = NULL;
    return module;
}