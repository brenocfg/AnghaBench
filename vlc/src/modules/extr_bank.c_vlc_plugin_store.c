#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* module; struct TYPE_7__* next; } ;
typedef  TYPE_1__ vlc_plugin_t ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_2__ module_t ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_6__ modules ; 
 int /*<<< orphan*/  vlc_module_store (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_plugins ; 

__attribute__((used)) static void vlc_plugin_store(vlc_plugin_t *lib)
{
    vlc_mutex_assert(&modules.lock);

    lib->next = vlc_plugins;
    vlc_plugins = lib;

    for (module_t *m = lib->module; m != NULL; m = m->next)
        vlc_module_store(m);
}