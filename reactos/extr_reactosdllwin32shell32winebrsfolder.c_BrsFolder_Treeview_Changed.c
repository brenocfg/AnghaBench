#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ pidlRet; int /*<<< orphan*/  hWnd; int /*<<< orphan*/  lpBrowseInfo; } ;
typedef  TYPE_2__ browse_info ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  lpi; int /*<<< orphan*/  lpsfParent; int /*<<< orphan*/  lpifq; } ;
struct TYPE_9__ {int /*<<< orphan*/  lParam; } ;
struct TYPE_11__ {TYPE_1__ itemNew; } ;
typedef  TYPE_3__ NMTREEVIEWW ;
typedef  TYPE_4__* LPTV_ITEMDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  BFFM_SELCHANGED ; 
 int /*<<< orphan*/  BrsFolder_CheckValidSelection (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_BROWSE_FOR_FOLDER_FOLDER_TEXT ; 
 scalar_t__ ILClone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILFree (scalar_t__) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHGDN_NORMAL ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  browsefolder_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT BrsFolder_Treeview_Changed( browse_info *info, NMTREEVIEWW *pnmtv )
{
    LPTV_ITEMDATA lptvid = (LPTV_ITEMDATA) pnmtv->itemNew.lParam;
    WCHAR name[MAX_PATH];

    ILFree(info->pidlRet);
    info->pidlRet = ILClone(lptvid->lpifq);

    if (GetName(lptvid->lpsfParent, lptvid->lpi, SHGDN_NORMAL, name))
            SetWindowTextW( GetDlgItem(info->hWnd, IDC_BROWSE_FOR_FOLDER_FOLDER_TEXT), name );

    browsefolder_callback( info->lpBrowseInfo, info->hWnd, BFFM_SELCHANGED,
                           (LPARAM)info->pidlRet );
    BrsFolder_CheckValidSelection( info, lptvid );
    return S_OK;
}