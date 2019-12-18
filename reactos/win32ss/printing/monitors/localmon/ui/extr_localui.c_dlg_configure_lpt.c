#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hXcv; } ;
typedef  TYPE_1__ lptconfig_t ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DialogBoxParamW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_CANCELLED ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOCALUI_hInstance ; 
 int /*<<< orphan*/  LPTCONFIG_DIALOG ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlgproc_lptconfig ; 

__attribute__((used)) static BOOL dlg_configure_lpt(HANDLE hXcv, HWND hWnd)
{
    lptconfig_t data;
    BOOL  res;


    data.hXcv = hXcv;

    res = DialogBoxParamW(LOCALUI_hInstance, MAKEINTRESOURCEW(LPTCONFIG_DIALOG), hWnd,
                               dlgproc_lptconfig, (LPARAM) &data);

    TRACE("got %u with %u\n", res, GetLastError());

    if (!res) SetLastError(ERROR_CANCELLED);
    return res;
}