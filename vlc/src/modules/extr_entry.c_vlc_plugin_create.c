#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ booleans; scalar_t__ count; scalar_t__ size; int /*<<< orphan*/ * items; } ;
struct TYPE_6__ {int unloadable; int /*<<< orphan*/ * module; int /*<<< orphan*/ * path; int /*<<< orphan*/ * abspath; int /*<<< orphan*/  handle; TYPE_1__ conf; int /*<<< orphan*/ * textdomain; scalar_t__ modules_count; } ;
typedef  TYPE_2__ vlc_plugin_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

vlc_plugin_t *vlc_plugin_create(void)
{
    vlc_plugin_t *plugin = malloc(sizeof (*plugin));
    if (unlikely(plugin == NULL))
        return NULL;

    plugin->modules_count = 0;
    plugin->textdomain = NULL;
    plugin->conf.items = NULL;
    plugin->conf.size = 0;
    plugin->conf.count = 0;
    plugin->conf.booleans = 0;
#ifdef HAVE_DYNAMIC_PLUGINS
    plugin->abspath = NULL;
    plugin->unloadable = true;
    atomic_init(&plugin->handle, 0);
    plugin->abspath = NULL;
    plugin->path = NULL;
#endif
    plugin->module = NULL;

    return plugin;
}