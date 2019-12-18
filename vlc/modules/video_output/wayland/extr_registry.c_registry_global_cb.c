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
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_registry {int dummy; } ;
struct vlc_wl_registry {int /*<<< orphan*/  names; int /*<<< orphan*/  interfaces; } ;
typedef  void vlc_wl_interface ;
typedef  void vlc_wl_global ;

/* Variables and functions */
 void** tsearch (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 void* vlc_wl_global_add (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_wl_global_remove (void*) ; 
 void* vlc_wl_interface_create (char const*) ; 
 int /*<<< orphan*/  vlc_wl_interface_destroy (void*) ; 
 int /*<<< orphan*/  vwicmp ; 
 int /*<<< orphan*/  vwncmp ; 

__attribute__((used)) static void registry_global_cb(void *data, struct wl_registry *registry,
                               uint32_t name, const char *iface, uint32_t vers)
{
    struct vlc_wl_registry *vr = data;
    struct vlc_wl_interface *vi = vlc_wl_interface_create(iface);

    void **pvi = tsearch(vi, &vr->interfaces, vwicmp);
    if (unlikely(pvi == NULL))
    {
        vlc_wl_interface_destroy(vi);
        return;
    }

    if (*pvi != vi)
    {
        vlc_wl_interface_destroy(vi);
        vi = *pvi;
    }

    struct vlc_wl_global *vg = vlc_wl_global_add(vi, name, vers);
    if (unlikely(vg == NULL))
        return;

    void **pvg = tsearch(vg, &vr->names, vwncmp);
    if (unlikely(pvg == NULL) /* OOM */
     || unlikely(*pvg != vg) /* display server bug */)
        vlc_wl_global_remove(vg);

    (void) registry;
}