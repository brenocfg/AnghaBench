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
struct vlc_wl_interface {int /*<<< orphan*/  globals; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vlc_wl_interface*) ; 
 int /*<<< orphan*/  wl_list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_wl_interface_destroy(struct vlc_wl_interface *vi)
{
    assert(wl_list_empty(&vi->globals));
    free(vi);
}