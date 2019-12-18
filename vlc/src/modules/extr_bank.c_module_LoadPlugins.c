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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_2__ {int usage; int /*<<< orphan*/  lock; int /*<<< orphan*/  caps_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateAllPlugins (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_SortConfig () ; 
 int /*<<< orphan*/  config_UnsortConfig () ; 
 int /*<<< orphan*/  module_InitStaticModules () ; 
 int /*<<< orphan*/  module_list_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** module_list_get (size_t*) ; 
 TYPE_1__ modules ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  twalk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_modcap_sort ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void module_LoadPlugins(vlc_object_t *obj)
{
    /*vlc_mutex_assert (&modules.lock); not for static mutexes :( */

    if (modules.usage == 1)
    {
        module_InitStaticModules ();
#ifdef HAVE_DYNAMIC_PLUGINS
        msg_Dbg (obj, "searching plug-in modules");
        AllocateAllPlugins (obj);
#endif
        config_UnsortConfig ();
        config_SortConfig ();

        twalk(modules.caps_tree, vlc_modcap_sort);
    }
    vlc_mutex_unlock (&modules.lock);

    size_t count;
    module_t **list = module_list_get (&count);
    module_list_free (list);
    msg_Dbg (obj, "plug-ins loaded: %zu modules", count);
}