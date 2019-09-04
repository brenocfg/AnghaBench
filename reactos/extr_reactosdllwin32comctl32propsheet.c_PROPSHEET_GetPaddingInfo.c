#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_2__ PADDING_INFO ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDC_TABCONTROL ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static PADDING_INFO PROPSHEET_GetPaddingInfo(HWND hwndDlg)
{
  HWND hwndTab = GetDlgItem(hwndDlg, IDC_TABCONTROL);
  RECT rcTab;
  PADDING_INFO padding;

  GetWindowRect(hwndTab, &rcTab);
  MapWindowPoints( 0, hwndDlg, (POINT *)&rcTab, 2 );

  padding.x = rcTab.left;
  padding.y = rcTab.top;

  return padding;
}