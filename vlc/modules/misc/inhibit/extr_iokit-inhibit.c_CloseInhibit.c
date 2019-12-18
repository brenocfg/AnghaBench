#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_6__ {scalar_t__ inh_assertion_id; scalar_t__ act_assertion_id; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;

/* Variables and functions */
 scalar_t__ IOPMAssertionRelease (scalar_t__) ; 
 scalar_t__ kIOPMNullAssertionID ; 
 scalar_t__ kIOReturnSuccess ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 

__attribute__((used)) static void CloseInhibit(vlc_object_t *obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t*)obj;
    vlc_inhibit_sys_t* sys = ih->p_sys;

    // Release remaining IOPMAssertion for inhibition, if any
    if (sys->inh_assertion_id != kIOPMNullAssertionID) {
        msg_Dbg(ih, "Releasing remaining IOPMAssertion (inhibition)");

        if (IOPMAssertionRelease(sys->inh_assertion_id) != kIOReturnSuccess) {
            msg_Warn(ih, "Failed releasing IOPMAssertion on termination");
        }
        sys->inh_assertion_id = kIOPMNullAssertionID;
    }

    // Release remaining IOPMAssertion for activity, if any
    if (sys->act_assertion_id != kIOPMNullAssertionID) {
        msg_Dbg(ih, "Releasing remaining IOPMAssertion (activity)");

        if (IOPMAssertionRelease(sys->act_assertion_id) != kIOReturnSuccess) {
            msg_Warn(ih, "Failed releasing IOPMAssertion on termination");
        }
        sys->act_assertion_id = kIOPMNullAssertionID;
    }
}