#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {char* pszText; int cchTextMax; int /*<<< orphan*/ * hItem; int /*<<< orphan*/  mask; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ TVITEMA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HTREEITEM ;

/* Variables and functions */
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVGN_CHILD ; 
 int /*<<< orphan*/  TVGN_NEXT ; 
 int /*<<< orphan*/  TVGN_ROOT ; 
 int /*<<< orphan*/  TVIF_TEXT ; 
 int /*<<< orphan*/  TVM_GETITEMA ; 
 int /*<<< orphan*/  TVM_GETNEXTITEM ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void get_item_names_string(HWND hwnd, HTREEITEM item, char *str)
{
    TVITEMA tvitem = { 0 };
    HTREEITEM child;
    char name[16];

    if (!item)
    {
        item = (HTREEITEM)SendMessageA(hwnd, TVM_GETNEXTITEM, TVGN_ROOT, 0);
        str[0] = 0;
    }

    child = (HTREEITEM)SendMessageA(hwnd, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)item);

    tvitem.mask = TVIF_TEXT;
    tvitem.hItem = item;
    tvitem.pszText = name;
    tvitem.cchTextMax = sizeof(name);
    SendMessageA(hwnd, TVM_GETITEMA, 0, (LPARAM)&tvitem);
    strcat(str, tvitem.pszText);

    while (child != NULL)
    {
        get_item_names_string(hwnd, child, str);
        child = (HTREEITEM)SendMessageA(hwnd, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)child);
    }
}