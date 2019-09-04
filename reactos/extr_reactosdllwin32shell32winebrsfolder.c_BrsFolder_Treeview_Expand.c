#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hwndTreeView; } ;
typedef  TYPE_2__ browse_info ;
struct TYPE_11__ {int /*<<< orphan*/  lpi; int /*<<< orphan*/  pEnumIL; int /*<<< orphan*/  lpifq; int /*<<< orphan*/ * lpsfParent; } ;
struct TYPE_8__ {int state; scalar_t__ hItem; int /*<<< orphan*/  lParam; } ;
struct TYPE_10__ {TYPE_1__ itemNew; } ;
typedef  TYPE_3__ NMTREEVIEWW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_4__* LPTV_ITEMDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillTreeView (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 int /*<<< orphan*/  IShellFolder_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TVIS_EXPANDEDONCE ; 
 int /*<<< orphan*/  TVM_SORTCHILDREN ; 
 int /*<<< orphan*/  _ILIsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ILIsMyComputer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT BrsFolder_Treeview_Expand( browse_info *info, NMTREEVIEWW *pnmtv )
{
    IShellFolder *lpsf2 = NULL;
    LPTV_ITEMDATA lptvid = (LPTV_ITEMDATA) pnmtv->itemNew.lParam;
    HRESULT r;

    TRACE("TVN_ITEMEXPANDINGA/W\n");

    if ((pnmtv->itemNew.state & TVIS_EXPANDEDONCE))
        return 0;

    if (!_ILIsEmpty(lptvid->lpi)) {
        r = IShellFolder_BindToObject( lptvid->lpsfParent, lptvid->lpi, 0,
                                       &IID_IShellFolder, (void**)&lpsf2 );
    } else {
        lpsf2 = lptvid->lpsfParent;
        IShellFolder_AddRef(lpsf2);
        r = S_OK;
    }

    if (SUCCEEDED(r))
    {
        FillTreeView( info, lpsf2, lptvid->lpifq, pnmtv->itemNew.hItem, lptvid->pEnumIL);
        IShellFolder_Release( lpsf2 );
    }

    /* My Computer is already sorted and trying to do a simple text
     * sort will only mess things up */
    if (!_ILIsMyComputer(lptvid->lpi))
        SendMessageW( info->hwndTreeView, TVM_SORTCHILDREN,
                      FALSE, (LPARAM)pnmtv->itemNew.hItem );

    return 0;
}