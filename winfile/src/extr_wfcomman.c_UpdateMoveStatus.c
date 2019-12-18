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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DROPEFFECT_MOVE ; 
 int /*<<< orphan*/  SB_SETTEXT ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TEXT (char*) ; 
 int /*<<< orphan*/  hwndStatus ; 

VOID 
UpdateMoveStatus(DWORD dwEffect)
{
	SendMessage(hwndStatus, SB_SETTEXT, 2, (LPARAM)(dwEffect == DROPEFFECT_MOVE ? TEXT("MOVE PENDING") : NULL));
}