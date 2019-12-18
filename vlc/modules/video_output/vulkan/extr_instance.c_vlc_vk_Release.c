#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  module; int /*<<< orphan*/  ref_count; } ;
typedef  TYPE_1__ vlc_vk_t ;

/* Variables and functions */
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

void vlc_vk_Release(vlc_vk_t *vk)
{
    if (!vlc_atomic_rc_dec(&vk->ref_count))
        return;
    module_unneed(vk, vk->module);
    vlc_object_delete(vk);
}