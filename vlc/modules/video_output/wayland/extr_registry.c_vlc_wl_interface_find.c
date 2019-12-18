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
struct vlc_wl_registry {int /*<<< orphan*/  interfaces; } ;
typedef  void vlc_wl_interface ;

/* Variables and functions */
 void** tfind (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vwimatch ; 

__attribute__((used)) static struct vlc_wl_interface *
vlc_wl_interface_find(const struct vlc_wl_registry *vr, const char *interface)
{
    void **pvi = tfind(interface, &vr->interfaces, vwimatch);

    return (pvi != NULL) ? *pvi : NULL;
}