#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int itemID1; int itemID2; int /*<<< orphan*/  dwLocaleId; int /*<<< orphan*/  itemData2; scalar_t__ itemData1; int /*<<< orphan*/  hwndItem; int /*<<< orphan*/  CtlID; int /*<<< orphan*/  CtlType; } ;
struct TYPE_7__ {int style; int nb_items; int /*<<< orphan*/  owner; int /*<<< orphan*/  locale; TYPE_1__* items; int /*<<< orphan*/  self; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  str; } ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ LB_DESCR ;
typedef  int INT ;
typedef  TYPE_3__ COMPAREITEMSTRUCT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_STRINGS (TYPE_2__*) ; 
 int LBS_SORT ; 
 int LISTBOX_lstrcmpiW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ODT_LISTBOX ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_COMPAREITEM ; 

__attribute__((used)) static INT LISTBOX_FindStringPos( LB_DESCR *descr, LPCWSTR str, BOOL exact )
{
    INT index, min, max, res;

    if (!(descr->style & LBS_SORT)) return -1;  /* Add it at the end */
    min = 0;
    max = descr->nb_items;
    while (min != max)
    {
        index = (min + max) / 2;
        if (HAS_STRINGS(descr))
            res = LISTBOX_lstrcmpiW( descr->locale, str, descr->items[index].str);
        else
        {
            COMPAREITEMSTRUCT cis;
            UINT id = (UINT)GetWindowLongPtrW( descr->self, GWLP_ID );

            cis.CtlType    = ODT_LISTBOX;
            cis.CtlID      = id;
            cis.hwndItem   = descr->self;
            /* note that some application (MetaStock) expects the second item
             * to be in the listbox */
            cis.itemID1    = -1;
            cis.itemData1  = (ULONG_PTR)str;
            cis.itemID2    = index;
            cis.itemData2  = descr->items[index].data;
            cis.dwLocaleId = descr->locale;
            res = SendMessageW( descr->owner, WM_COMPAREITEM, id, (LPARAM)&cis );
        }
        if (!res) return index;
        if (res < 0) max = index;
        else min = index + 1;
    }
    return exact ? -1 : max;
}