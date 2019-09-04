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
struct TYPE_3__ {int member_0; int* rgstate; } ;
typedef  TYPE_1__ SCROLLBARINFO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GetScrollBarInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int STATE_SYSTEM_OFFSCREEN ; 

BOOL
IsScrollBarVisible(HWND hWnd, INT hBar)
{
  SCROLLBARINFO sbi = {sizeof(SCROLLBARINFO)};
  if(!GetScrollBarInfo(hWnd, hBar, &sbi))
    return FALSE;

  return !(sbi.rgstate[0] & STATE_SYSTEM_OFFSCREEN);
}