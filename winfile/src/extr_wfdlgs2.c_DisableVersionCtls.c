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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDD_VERSION_FRAME ; 
 int /*<<< orphan*/  IDD_VERSION_KEY ; 
 int /*<<< orphan*/  IDD_VERSION_VALUE ; 

VOID
DisableVersionCtls(HWND hDlg)
{
   EnableWindow(GetDlgItem(hDlg, IDD_VERSION_FRAME), FALSE);
   EnableWindow(GetDlgItem(hDlg, IDD_VERSION_KEY), FALSE);
   EnableWindow(GetDlgItem(hDlg, IDD_VERSION_VALUE), FALSE);
}