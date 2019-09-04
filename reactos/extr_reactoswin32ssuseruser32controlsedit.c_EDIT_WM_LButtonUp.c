#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ hwndSelf; scalar_t__ bCaptureState; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ GetCapture () ; 
 int /*<<< orphan*/  KillTimer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 

__attribute__((used)) static LRESULT EDIT_WM_LButtonUp(EDITSTATE *es)
{
	if (es->bCaptureState) {
		KillTimer(es->hwndSelf, 0);
		if (GetCapture() == es->hwndSelf) ReleaseCapture();
	}
	es->bCaptureState = FALSE;
	return 0;
}