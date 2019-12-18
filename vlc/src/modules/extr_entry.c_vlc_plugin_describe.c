#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_plugin_t ;
typedef  scalar_t__ (* vlc_plugin_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_plugin_create () ; 
 int /*<<< orphan*/  vlc_plugin_desc_cb ; 
 int /*<<< orphan*/  vlc_plugin_destroy (int /*<<< orphan*/ *) ; 

vlc_plugin_t *vlc_plugin_describe(vlc_plugin_cb entry)
{
    vlc_plugin_t *plugin = vlc_plugin_create();
    if (unlikely(plugin == NULL))
        return NULL;

    if (entry(vlc_plugin_desc_cb, plugin) != 0)
    {
        vlc_plugin_destroy(plugin); /* partially initialized plug-in... */
        plugin = NULL;
    }
    return plugin;
}