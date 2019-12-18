#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  inhibit; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_5__ {void* inh_assertion_id; void* act_assertion_id; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  UpdateInhibit ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 void* kIOPMNullAssertionID ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int OpenInhibit(vlc_object_t *obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t *)obj;

    // Intialize module private storage
    vlc_inhibit_sys_t *sys = ih->p_sys =
            vlc_obj_malloc(obj, sizeof(vlc_inhibit_sys_t));
    if (unlikely(ih->p_sys == NULL))
        return VLC_ENOMEM;

    sys->act_assertion_id = kIOPMNullAssertionID;
    sys->inh_assertion_id = kIOPMNullAssertionID;

    ih->inhibit = UpdateInhibit;
    return VLC_SUCCESS;
}