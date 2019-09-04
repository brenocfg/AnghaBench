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
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  AppInstance ; 
 int BS_AUTOCHECKBOX ; 
 int BS_AUTORADIOBUTTON ; 
 int BS_DEFPUSHBUTTON ; 
 int BS_PUSHBUTTON ; 
 int /*<<< orphan*/  BUTTON_CLASS ; 
 int /*<<< orphan*/  CreateWindowEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 

LRESULT WmCreate(
   HWND Wnd)
{
   DPRINT("WM_CREATE (enter).");
   DPRINT("test 1");
   CreateWindowEx(0, BUTTON_CLASS, "PushButton", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
      10, 10, 150, 30, Wnd, NULL, AppInstance, NULL);
   DPRINT("test 2");
   CreateWindowEx(0, BUTTON_CLASS, "DefPushButton", BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE,
      10, 40, 150, 30, Wnd, NULL, AppInstance, NULL);
   DPRINT("test 3");
   CreateWindowEx(0, BUTTON_CLASS, "AutoRadioButton", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
      10, 70, 150, 30, Wnd, NULL, AppInstance, NULL);
   DPRINT("test 4");
   CreateWindowEx(0, BUTTON_CLASS, "AutoCheckBox", BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
      10, 100, 150, 30, Wnd, NULL, AppInstance, NULL);

   DPRINT("WM_CREATE (leave).");
   return 0;
}