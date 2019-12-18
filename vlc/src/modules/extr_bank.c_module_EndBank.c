#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ vlc_plugin_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_7__ {scalar_t__ usage; int /*<<< orphan*/  lock; int /*<<< orphan*/ * caps_tree; int /*<<< orphan*/ * caches; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_UnsortConfig () ; 
 int /*<<< orphan*/  module_Unmap (TYPE_1__*) ; 
 TYPE_4__ modules ; 
 int /*<<< orphan*/  tdestroy (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_modcap_free ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_plugin_destroy (TYPE_1__*) ; 
 TYPE_1__* vlc_plugins ; 

void module_EndBank (bool b_plugins)
{
    vlc_plugin_t *libs = NULL;
    block_t *caches = NULL;
    void *caps_tree = NULL;

    /* If plugins were _not_ loaded, then the caller still has the bank lock
     * from module_InitBank(). */
    if( b_plugins )
        vlc_mutex_lock (&modules.lock);
    else
        vlc_mutex_assert(&modules.lock);

    assert (modules.usage > 0);
    if (--modules.usage == 0)
    {
        config_UnsortConfig ();
        libs = vlc_plugins;
        caches = modules.caches;
        caps_tree = modules.caps_tree;
        vlc_plugins = NULL;
        modules.caches = NULL;
        modules.caps_tree = NULL;
    }
    vlc_mutex_unlock (&modules.lock);

    tdestroy(caps_tree, vlc_modcap_free);

    while (libs != NULL)
    {
        vlc_plugin_t *lib = libs;

        libs = lib->next;
        module_Unmap(lib);
        vlc_plugin_destroy(lib);
    }

    block_ChainRelease(caches);
}