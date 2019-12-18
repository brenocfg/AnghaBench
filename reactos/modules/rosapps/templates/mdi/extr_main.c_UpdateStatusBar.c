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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetComputerName (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GetUserName (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SB_SETTEXT ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hStatusBar ; 

void UpdateStatusBar(void)
{
    TCHAR text[260];
    DWORD size;

    size = sizeof(text)/sizeof(TCHAR);
    GetUserName(text, &size);
    SendMessage(hStatusBar, SB_SETTEXT, 1, (LPARAM)text);
    size = sizeof(text)/sizeof(TCHAR);
    GetComputerName(text, &size);
    SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)text);
}