#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_11__ {int /*<<< orphan*/  lParam; scalar_t__ iSubItem; void* iItem; int /*<<< orphan*/  mask; } ;
struct TYPE_10__ {int /*<<< orphan*/  lParam; void* iItem; } ;
typedef  TYPE_1__ NMLISTVIEW ;
typedef  TYPE_2__ LVITEMW ;
typedef  TYPE_3__ LISTVIEW_INFO ;
typedef  void* INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ LISTVIEW_GetItemT (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVIF_PARAM ; 
 int /*<<< orphan*/  LVN_DELETEITEM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  notify_listview (TYPE_3__ const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static BOOL notify_deleteitem(const LISTVIEW_INFO *infoPtr, INT nItem)
{
    NMLISTVIEW nmlv;
    LVITEMW item;
    HWND hwnd = infoPtr->hwndSelf;

    ZeroMemory(&nmlv, sizeof (NMLISTVIEW));
    nmlv.iItem = nItem;
    item.mask = LVIF_PARAM;
    item.iItem = nItem;
    item.iSubItem = 0;
    if (LISTVIEW_GetItemT(infoPtr, &item, TRUE)) nmlv.lParam = item.lParam;
    notify_listview(infoPtr, LVN_DELETEITEM, &nmlv);
    return IsWindow(hwnd);
}