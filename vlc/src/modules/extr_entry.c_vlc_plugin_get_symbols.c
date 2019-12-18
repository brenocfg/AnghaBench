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
typedef  scalar_t__ (* vlc_plugin_cb ) (int /*<<< orphan*/ ,void**) ;

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  tdestroy (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_plugin_gpa_cb ; 

__attribute__((used)) static void *vlc_plugin_get_symbols(vlc_plugin_cb entry)
{
    void *root = NULL;

    if (entry(vlc_plugin_gpa_cb, &root))
    {
        tdestroy(root, free);
        return NULL;
    }

    return root;
}