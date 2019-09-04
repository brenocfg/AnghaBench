#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item ;
struct TYPE_8__ {int /*<<< orphan*/  hwndTreeView; TYPE_1__* lpBrowseInfo; } ;
typedef  TYPE_2__ browse_info ;
struct TYPE_10__ {scalar_t__ lpi; } ;
struct TYPE_9__ {void* hItem; scalar_t__ lParam; int /*<<< orphan*/  mask; } ;
struct TYPE_7__ {scalar_t__ pidlRoot; } ;
typedef  TYPE_3__ TVITEMEXW ;
typedef  scalar_t__ LPVOID ;
typedef  TYPE_4__* LPTV_ITEMDATA ;
typedef  scalar_t__ LPITEMIDLIST ;
typedef  scalar_t__ LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  void* HTREEITEM ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ILFree (scalar_t__) ; 
 scalar_t__ ILGetNext (scalar_t__) ; 
 int /*<<< orphan*/  IShellFolder_ParseDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TVE_EXPAND ; 
 int /*<<< orphan*/  TVGN_CHILD ; 
 int /*<<< orphan*/  TVGN_NEXT ; 
 int /*<<< orphan*/  TVGN_ROOT ; 
 int /*<<< orphan*/  TVIF_PARAM ; 
 int /*<<< orphan*/  TVM_EXPAND ; 
 int /*<<< orphan*/  TVM_GETITEMW ; 
 int /*<<< orphan*/  TVM_GETNEXTITEM ; 
 scalar_t__ _ILIsEmpty (scalar_t__) ; 
 scalar_t__ _ILIsEqualSimple (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL BrsFolder_OnSetExpanded(browse_info *info, LPVOID selection, 
    BOOL is_str, HTREEITEM *pItem)
{
    LPITEMIDLIST pidlSelection = selection;
    LPCITEMIDLIST pidlCurrent, pidlRoot;
    TVITEMEXW item;
    BOOL bResult = FALSE;

    memset(&item, 0, sizeof(item));

    /* If 'selection' is a string, convert to a Shell ID List. */ 
    if (is_str) {
        IShellFolder *psfDesktop;
        HRESULT hr;

        hr = SHGetDesktopFolder(&psfDesktop);
        if (FAILED(hr))
            goto done;

        hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, 
                     selection, NULL, &pidlSelection, NULL);
        IShellFolder_Release(psfDesktop);
        if (FAILED(hr)) 
            goto done;
    }

    /* Move pidlCurrent behind the SHITEMIDs in pidlSelection, which are the root of
     * the sub-tree currently displayed. */
    pidlRoot = info->lpBrowseInfo->pidlRoot;
    pidlCurrent = pidlSelection;
    while (!_ILIsEmpty(pidlRoot) && _ILIsEqualSimple(pidlRoot, pidlCurrent)) {
        pidlRoot = ILGetNext(pidlRoot);
        pidlCurrent = ILGetNext(pidlCurrent);
    }

    /* The given ID List is not part of the SHBrowseForFolder's current sub-tree. */
    if (!_ILIsEmpty(pidlRoot))
        goto done;

    /* Initialize item to point to the first child of the root folder. */
    item.mask = TVIF_PARAM;
    item.hItem = (HTREEITEM)SendMessageW(info->hwndTreeView, TVM_GETNEXTITEM, TVGN_ROOT, 0);

    if (item.hItem)
        item.hItem = (HTREEITEM)SendMessageW(info->hwndTreeView, TVM_GETNEXTITEM, TVGN_CHILD,
                                             (LPARAM)item.hItem);

    /* Walk the tree along the nodes corresponding to the remaining ITEMIDLIST */
    while (item.hItem && !_ILIsEmpty(pidlCurrent)) {
        LPTV_ITEMDATA pItemData;

        SendMessageW(info->hwndTreeView, TVM_GETITEMW, 0, (LPARAM)&item);
        pItemData = (LPTV_ITEMDATA)item.lParam;

        if (_ILIsEqualSimple(pItemData->lpi, pidlCurrent)) {
            pidlCurrent = ILGetNext(pidlCurrent);
            if (!_ILIsEmpty(pidlCurrent)) {
                /* Only expand current node and move on to its first child,
                 * if we didn't already reach the last SHITEMID */
                SendMessageW(info->hwndTreeView, TVM_EXPAND, TVE_EXPAND, (LPARAM)item.hItem);
                item.hItem = (HTREEITEM)SendMessageW(info->hwndTreeView, TVM_GETNEXTITEM, TVGN_CHILD,
                                             (LPARAM)item.hItem);
            }
        } else {
            item.hItem = (HTREEITEM)SendMessageW(info->hwndTreeView, TVM_GETNEXTITEM, TVGN_NEXT,
                                             (LPARAM)item.hItem);
        }
    }

    if (_ILIsEmpty(pidlCurrent) && item.hItem) 
        bResult = TRUE;

done:
    if (pidlSelection && pidlSelection != selection)
        ILFree(pidlSelection);

    if (pItem) 
        *pItem = item.hItem;
    
    return bResult;
}