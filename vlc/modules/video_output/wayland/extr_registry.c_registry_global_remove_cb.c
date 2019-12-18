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
struct vlc_wl_registry {int /*<<< orphan*/  names; } ;
struct vlc_wl_global {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdelete (struct vlc_wl_global*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void** tfind (struct vlc_wl_global*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_wl_global_remove (struct vlc_wl_global*) ; 
 int /*<<< orphan*/  vwncmp ; 

__attribute__((used)) static void registry_global_remove_cb(void *data, struct wl_registry *registry,
                                      uint32_t name)
{
    struct vlc_wl_registry *vr = data;
    struct vlc_wl_global key = { .name = name };
    void **pvg = tfind(&key, &vr->names, vwncmp);

    if (likely(pvg != NULL))
    {
        struct vlc_wl_global *vg = *pvg;

        tdelete(vg, &vr->names, vwncmp);
        vlc_wl_global_remove(vg);
    }

    (void) registry;
}