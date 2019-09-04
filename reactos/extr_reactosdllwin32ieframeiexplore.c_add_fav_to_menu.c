#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_3__ {int cbSize; int fMask; int wID; scalar_t__ dwItemData; scalar_t__ dwTypeData; int /*<<< orphan*/  fType; } ;
typedef  TYPE_1__ MENUITEMINFOW ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int ID_BROWSE_GOTOFAV_FIRST ; 
 int ID_BROWSE_GOTOFAV_MAX ; 
 int /*<<< orphan*/  InsertMenuItemW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MFT_STRING ; 
 int MIIM_DATA ; 
 int MIIM_FTYPE ; 
 int MIIM_ID ; 
 int MIIM_STRING ; 
 int /*<<< orphan*/  TRUE ; 
 int get_menu_item_count (int /*<<< orphan*/ ) ; 
 scalar_t__ heap_alloc (int) ; 
 int /*<<< orphan*/  lstrcpyW (scalar_t__,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_fav_to_menu(HMENU favmenu, HMENU menu, LPWSTR title, LPCWSTR url)
{
    MENUITEMINFOW item;
    /* Subtract the number of standard elements in the Favorites menu */
    int favcount = get_menu_item_count(favmenu) - 2;
    LPWSTR urlbuf;

    if(favcount > (ID_BROWSE_GOTOFAV_MAX - ID_BROWSE_GOTOFAV_FIRST))
    {
        FIXME("Add support for more than %d Favorites\n", favcount);
        return;
    }

    urlbuf = heap_alloc((lstrlenW(url) + 1) * sizeof(WCHAR));

    if(!urlbuf)
        return;

    lstrcpyW(urlbuf, url);

    item.cbSize = sizeof(item);
    item.fMask = MIIM_FTYPE | MIIM_STRING | MIIM_DATA | MIIM_ID;
    item.fType = MFT_STRING;
    item.dwTypeData = title;
    item.wID = ID_BROWSE_GOTOFAV_FIRST + favcount;
    item.dwItemData = (ULONG_PTR)urlbuf;
    InsertMenuItemW(menu, -1, TRUE, &item);
}