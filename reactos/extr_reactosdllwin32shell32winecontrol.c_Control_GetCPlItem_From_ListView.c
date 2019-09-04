#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hWndListView; } ;
struct TYPE_4__ {int iItem; scalar_t__ lParam; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ LVITEMW ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  CPlItem ;
typedef  TYPE_2__ CPanel ;

/* Variables and functions */
 int /*<<< orphan*/  LVIF_PARAM ; 
 int /*<<< orphan*/  LVM_GETITEMW ; 
 int /*<<< orphan*/  LVM_GETNEXTITEM ; 
 int LVNI_FOCUSED ; 
 int LVNI_SELECTED ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static CPlItem* Control_GetCPlItem_From_ListView(CPanel *panel)
{
    LVITEMW lvItem;
    int selitem;

    selitem = SendMessageW(panel->hWndListView, LVM_GETNEXTITEM, -1, LVNI_FOCUSED
        | LVNI_SELECTED);

    if (selitem != -1)
    {
        lvItem.iItem = selitem;
        lvItem.mask = LVIF_PARAM;

        if (SendMessageW(panel->hWndListView, LVM_GETITEMW, 0, (LPARAM) &lvItem))
            return (CPlItem *) lvItem.lParam;
    }

    return NULL;
}