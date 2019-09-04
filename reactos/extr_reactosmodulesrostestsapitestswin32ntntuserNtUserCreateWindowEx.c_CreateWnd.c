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
typedef  int /*<<< orphan*/  PLARGE_STRING ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/  NtUserCreateWindowEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WS_CAPTION ; 
 int /*<<< orphan*/  WS_EX_OVERLAPPEDWINDOW ; 

__attribute__((used)) static
inline
HWND
CreateWnd(HINSTANCE hinst,
          PLARGE_STRING clsName,
          PLARGE_STRING clsVer,
          PLARGE_STRING wndName)
{
    return NtUserCreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
                                clsName,
                                clsVer,
                                wndName,
                                WS_CAPTION,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                100,
                                100,
                                NULL,
                                NULL,
                                hinst,
                                0,
                                0,
                                NULL);
}