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
struct vlc_wl_registry {int /*<<< orphan*/  interfaces; int /*<<< orphan*/  names; int /*<<< orphan*/  registry; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_wl_registry*) ; 
 int /*<<< orphan*/  interface_destroy ; 
 int /*<<< orphan*/  name_destroy ; 
 int /*<<< orphan*/  tdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_registry_destroy (int /*<<< orphan*/ ) ; 

void vlc_wl_registry_destroy(struct vlc_wl_registry *vr)
{
    wl_registry_destroy(vr->registry);
    tdestroy(vr->names, name_destroy);
    tdestroy(vr->interfaces, interface_destroy);
    free(vr);
}