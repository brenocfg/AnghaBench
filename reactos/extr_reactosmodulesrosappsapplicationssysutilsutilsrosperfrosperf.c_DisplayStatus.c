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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  Status ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DisplayStatus(HWND Label, LPCWSTR Message, LPCWSTR Test, int Try)
{
  WCHAR Status[128];

  _snwprintf(Status, sizeof(Status) / sizeof(Status[0]), L"%d %s %s", Try, Message, Test);
  SetWindowTextW(Label, Status);
  InvalidateRect(Label, NULL, TRUE);
  UpdateWindow(Label);
}