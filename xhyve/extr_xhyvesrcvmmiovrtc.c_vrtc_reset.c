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
struct rtcdev {int reg_b; } ;
struct vrtc {int /*<<< orphan*/  callout; struct rtcdev rtcdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RTCSB_ALL_INTRS ; 
 int RTCSB_SQWE ; 
 int /*<<< orphan*/  VRTC_LOCK (struct vrtc*) ; 
 int /*<<< orphan*/  VRTC_UNLOCK (struct vrtc*) ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrtc_set_reg_b (struct vrtc*,int) ; 
 int /*<<< orphan*/  vrtc_set_reg_c (struct vrtc*,int /*<<< orphan*/ ) ; 

void
vrtc_reset(struct vrtc *vrtc)
{
	struct rtcdev *rtc;

	VRTC_LOCK(vrtc);

	rtc = &vrtc->rtcdev;
	vrtc_set_reg_b(vrtc, rtc->reg_b & ~(RTCSB_ALL_INTRS | RTCSB_SQWE));
	vrtc_set_reg_c(vrtc, 0);
	KASSERT(!callout_active(&vrtc->callout), ("rtc callout still active"));

	VRTC_UNLOCK(vrtc);
}