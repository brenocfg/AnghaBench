#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ self; int style; scalar_t__ nb_items; scalar_t__ captured; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ LB_DESCR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ GetCapture () ; 
 int /*<<< orphan*/  KillSystemTimer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LBN_SELCHANGE ; 
 int LBS_NOTIFY ; 
 int /*<<< orphan*/  LB_TIMER_ID ; 
 scalar_t__ LB_TIMER_NONE ; 
 scalar_t__ LISTBOX_Timer ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SEND_NOTIFICATION (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT LISTBOX_HandleLButtonUp( LB_DESCR *descr )
{
    if (LISTBOX_Timer != LB_TIMER_NONE)
        KillSystemTimer( descr->self, LB_TIMER_ID );
    LISTBOX_Timer = LB_TIMER_NONE;
    if (descr->captured)
    {
        descr->captured = FALSE;
        if (GetCapture() == descr->self) ReleaseCapture();
        if ((descr->style & LBS_NOTIFY) && descr->nb_items)
            SEND_NOTIFICATION( descr, LBN_SELCHANGE );
    }
    return 0;
}