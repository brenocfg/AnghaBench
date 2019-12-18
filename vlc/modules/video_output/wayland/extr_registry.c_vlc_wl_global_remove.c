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
struct vlc_wl_global {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_wl_global*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_wl_global_remove(struct vlc_wl_global *vg)
{
    wl_list_remove(&vg->node);
    free(vg);
}