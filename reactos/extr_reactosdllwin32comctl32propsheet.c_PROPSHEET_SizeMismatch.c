#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {scalar_t__ right; scalar_t__ left; scalar_t__ bottom; scalar_t__ top; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ PropSheetInfo ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_TABCONTROL ; 
 int /*<<< orphan*/  MapDialogRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static BOOL PROPSHEET_SizeMismatch(HWND hwndDlg, const PropSheetInfo* psInfo)
{
  HWND hwndTabCtrl = GetDlgItem(hwndDlg, IDC_TABCONTROL);
  RECT rcOrigTab, rcPage;

  /*
   * Original tab size.
   */
  GetClientRect(hwndTabCtrl, &rcOrigTab);
  TRACE("orig tab %s\n", wine_dbgstr_rect(&rcOrigTab));

  /*
   * Biggest page size.
   */
  SetRect(&rcPage, 0, 0, psInfo->width, psInfo->height);
  MapDialogRect(hwndDlg, &rcPage);
  TRACE("biggest page %s\n", wine_dbgstr_rect(&rcPage));

  if ( (rcPage.right - rcPage.left) != (rcOrigTab.right - rcOrigTab.left) )
    return TRUE;
  if ( (rcPage.bottom - rcPage.top) != (rcOrigTab.bottom - rcOrigTab.top) )
    return TRUE;

  return FALSE;
}