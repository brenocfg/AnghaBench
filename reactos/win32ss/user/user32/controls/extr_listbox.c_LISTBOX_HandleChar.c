#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_8__ {int style; int selected_item; scalar_t__ nb_items; int /*<<< orphan*/  focus_item; scalar_t__ self; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ LB_DESCR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IS_MULTISELECT (TYPE_1__*) ; 
 int /*<<< orphan*/  LBN_SELCHANGE ; 
 int LBS_NOTIFY ; 
 int LBS_WANTKEYBOARDINPUT ; 
 int LISTBOX_FindString (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_MoveCaret (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_SetSelection (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWPARAM (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_NOTIFICATION (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_CHARTOITEM ; 

__attribute__((used)) static LRESULT LISTBOX_HandleChar( LB_DESCR *descr, WCHAR charW )
{
    INT caret = -1;
    WCHAR str[2];

    str[0] = charW;
    str[1] = '\0';

    if (descr->style & LBS_WANTKEYBOARDINPUT)
    {
        caret = SendMessageW( descr->owner, WM_CHARTOITEM,
                                MAKEWPARAM(charW, descr->focus_item),
                                (LPARAM)descr->self );
        if (caret == -2) return 0;
    }
    if (caret == -1)
        caret = LISTBOX_FindString( descr, descr->focus_item, str, FALSE);
    if (caret != -1)
    {
        if ((!IS_MULTISELECT(descr)) && descr->selected_item == -1)
           LISTBOX_SetSelection( descr, caret, TRUE, FALSE);
        LISTBOX_MoveCaret( descr, caret, TRUE );
        if ((descr->style & LBS_NOTIFY) && descr->nb_items)
            SEND_NOTIFICATION( descr, LBN_SELCHANGE );
    }
    return 0;
}