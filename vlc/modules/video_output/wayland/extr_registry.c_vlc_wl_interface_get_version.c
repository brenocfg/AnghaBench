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
typedef  int /*<<< orphan*/  uint_fast32_t ;
struct vlc_wl_registry {int dummy; } ;
struct vlc_wl_global {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 struct vlc_wl_global* vlc_wl_global_find (struct vlc_wl_registry*,char const*) ; 

uint_fast32_t vlc_wl_interface_get_version(struct vlc_wl_registry *vr,
                                           const char *interface)
{
    const struct vlc_wl_global *vg = vlc_wl_global_find(vr, interface);

    return (vg != NULL) ? vg->version : 0;
}