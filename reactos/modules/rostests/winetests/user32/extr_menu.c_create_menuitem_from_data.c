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
struct menu_data {int type; scalar_t__ str; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int member_0; int fMask; int fType; int /*<<< orphan*/  wID; scalar_t__ fState; int /*<<< orphan*/  cch; scalar_t__ dwTypeData; scalar_t__ hbmpItem; } ;
typedef  TYPE_1__ MENUITEMINFOA ;
typedef  scalar_t__ LPSTR ;
typedef  size_t INT ;
typedef  scalar_t__ HMENU ;
typedef  scalar_t__ HBITMAP ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CreateMenu () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  InsertMenuItemA (scalar_t__,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int MFT_BITMAP ; 
 int MFT_SEPARATOR ; 
 int MF_HELP ; 
 int MIIM_BITMAP ; 
 int MIIM_FTYPE ; 
 int MIIM_ID ; 
 int MIIM_STATE ; 
 int MIIM_STRING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,size_t,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static HMENU create_menuitem_from_data(const struct menu_data *item, INT item_count)
{
    HMENU hmenu;
    INT i;
    BOOL ret;
    MENUITEMINFOA mii = { sizeof( MENUITEMINFOA) };

    hmenu = CreateMenu();
    assert(hmenu != 0);

    for (i = 0; i < item_count; i++)
    {
        SetLastError(0xdeadbeef);

        mii.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STATE;
        mii.fType = 0;
        if(  item[i].type & MFT_BITMAP)
        {
            mii.fMask |= MIIM_BITMAP;
            mii.hbmpItem =  (HBITMAP)item[i].str;
        }
        else if(  item[i].type & MFT_SEPARATOR)
            mii.fType = MFT_SEPARATOR;
        else
        {
            mii.fMask |= MIIM_STRING;
            mii.dwTypeData =  (LPSTR)item[i].str;
            mii.cch = strlen(  item[i].str);
        }
        mii.fState = 0;
        if(  item[i].type & MF_HELP) mii.fType |= MF_HELP;
        mii.wID = item[i].id;
        ret = InsertMenuItemA( hmenu, -1, TRUE, &mii);
        ok(ret, "%d: InsertMenuItem(%04x, %04x, %p) error %u\n",
           i, item[i].type, item[i].id, item[i].str, GetLastError());
    }
    return hmenu;
}