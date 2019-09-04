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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int DLGC_HASSETSEL ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETDLGCODE ; 

__attribute__((used)) static void DEFDLG_SetFocus( HWND hwndCtrl )
{
    if (SendMessageW( hwndCtrl, WM_GETDLGCODE, 0, 0 ) & DLGC_HASSETSEL)
        SendMessageW( hwndCtrl, EM_SETSEL, 0, -1 );
    SetFocus( hwndCtrl );
}