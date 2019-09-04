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
struct vrtc {int /*<<< orphan*/  callout; int /*<<< orphan*/  vm; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int SBT_1S ; 
 int /*<<< orphan*/  VM_CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vrtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrtc_callout_handler ; 

__attribute__((used)) static void
vrtc_callout_reset(struct vrtc *vrtc, sbintime_t freqsbt)
{
	if (freqsbt == 0) {
		if (callout_active(&vrtc->callout)) {
			VM_CTR0(vrtc->vm, "RTC callout stopped");
			callout_stop(&vrtc->callout);
		}
		return;
	}
	VM_CTR1(vrtc->vm, "RTC callout frequency %lld hz", SBT_1S / freqsbt);
	callout_reset_sbt(&vrtc->callout, freqsbt, 0, vrtc_callout_handler,
	    vrtc, 0);
}