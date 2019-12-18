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
typedef  int uint32_t ;
struct wl_proxy {int dummy; } ;
struct wl_interface {int dummy; } ;
struct vlc_wl_registry {int /*<<< orphan*/  registry; } ;
struct vlc_wl_global {int version; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct vlc_wl_global* vlc_wl_global_find (struct vlc_wl_registry*,char const*) ; 
 struct wl_proxy* wl_registry_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl_interface const*,int) ; 

struct wl_proxy *vlc_wl_interface_bind(struct vlc_wl_registry *vr,
                                       const char *interface,
                                       const struct wl_interface *wi,
                                       uint32_t *restrict version)
{
    const struct vlc_wl_global *vg = vlc_wl_global_find(vr, interface);

    if (vg == NULL)
        return 0;

    uint32_t vers = (version != NULL) ? *version : 1;

    if (vers > vg->version)
        *version = vers = vg->version;

    return wl_registry_bind(vr->registry, vg->name, wi, vers);
}