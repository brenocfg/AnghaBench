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
struct TYPE_4__ {int unloadable; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ vlc_plugin_t ;
typedef  int /*<<< orphan*/  vlc_plugin_cb ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_plugin_describe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_plugin_t *module_InitStatic(vlc_plugin_cb entry)
{
    /* Initializes the statically-linked library */
    vlc_plugin_t *lib = vlc_plugin_describe (entry);
    if (unlikely(lib == NULL))
        return NULL;

#ifdef HAVE_DYNAMIC_PLUGINS
    atomic_init(&lib->handle, 0);
    lib->unloadable = false;
#endif
    return lib;
}