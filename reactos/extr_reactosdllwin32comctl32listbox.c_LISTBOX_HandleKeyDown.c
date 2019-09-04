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
struct TYPE_12__ {int selected_item; int focus_item; int style; int page_size; int nb_items; int width; int column_width; int anchor_item; TYPE_2__* lphc; scalar_t__ self; TYPE_1__* items; int /*<<< orphan*/  owner; } ;
struct TYPE_11__ {int /*<<< orphan*/  wState; } ;
struct TYPE_10__ {int /*<<< orphan*/  selected; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_3__ LB_DESCR ;
typedef  int INT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CBF_NOROLLUP ; 
 int FALSE ; 
 int GetKeyState (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_MULTISELECT (TYPE_3__*) ; 
 scalar_t__ IsWindowVisible (scalar_t__) ; 
 int /*<<< orphan*/  LBN_SELCHANGE ; 
 int LBS_EXTENDEDSEL ; 
 int LBS_MULTICOLUMN ; 
 int LBS_MULTIPLESEL ; 
 int LBS_NOTIFY ; 
 int LBS_WANTKEYBOARDINPUT ; 
 int /*<<< orphan*/  LISTBOX_GetCurrentPageSize (TYPE_3__*) ; 
 int /*<<< orphan*/  LISTBOX_MoveCaret (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  LISTBOX_SetSelection (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  LOWORD (int) ; 
 int /*<<< orphan*/  MAKEWPARAM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SEND_NOTIFICATION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
#define  VK_DOWN 136 
#define  VK_END 135 
#define  VK_HOME 134 
#define  VK_LEFT 133 
#define  VK_NEXT 132 
#define  VK_PRIOR 131 
#define  VK_RIGHT 130 
 int /*<<< orphan*/  VK_SHIFT ; 
#define  VK_SPACE 129 
#define  VK_UP 128 
 int /*<<< orphan*/  WM_VKEYTOITEM ; 

__attribute__((used)) static LRESULT LISTBOX_HandleKeyDown( LB_DESCR *descr, DWORD key )
{
    INT caret = -1;
    BOOL bForceSelection = TRUE; /* select item pointed to by focus_item */
    if ((IS_MULTISELECT(descr)) || (descr->selected_item == descr->focus_item))
        bForceSelection = FALSE; /* only for single select list */

    if (descr->style & LBS_WANTKEYBOARDINPUT)
    {
        caret = SendMessageW( descr->owner, WM_VKEYTOITEM,
                                MAKEWPARAM(LOWORD(key), descr->focus_item),
                                (LPARAM)descr->self );
        if (caret == -2) return 0;
    }
    if (caret == -1) switch(key)
    {
    case VK_LEFT:
        if (descr->style & LBS_MULTICOLUMN)
        {
            bForceSelection = FALSE;
            if (descr->focus_item >= descr->page_size)
                caret = descr->focus_item - descr->page_size;
            break;
        }
        /* fall through */
    case VK_UP:
        caret = descr->focus_item - 1;
        if (caret < 0) caret = 0;
        break;
    case VK_RIGHT:
        if (descr->style & LBS_MULTICOLUMN)
        {
            bForceSelection = FALSE;
            if (descr->focus_item + descr->page_size < descr->nb_items)
                caret = descr->focus_item + descr->page_size;
            break;
        }
        /* fall through */
    case VK_DOWN:
        caret = descr->focus_item + 1;
        if (caret >= descr->nb_items) caret = descr->nb_items - 1;
        break;

    case VK_PRIOR:
        if (descr->style & LBS_MULTICOLUMN)
        {
            INT page = descr->width / descr->column_width;
            if (page < 1) page = 1;
            caret = descr->focus_item - (page * descr->page_size) + 1;
        }
        else caret = descr->focus_item-LISTBOX_GetCurrentPageSize(descr) + 1;
        if (caret < 0) caret = 0;
        break;
    case VK_NEXT:
        if (descr->style & LBS_MULTICOLUMN)
        {
            INT page = descr->width / descr->column_width;
            if (page < 1) page = 1;
            caret = descr->focus_item + (page * descr->page_size) - 1;
        }
        else caret = descr->focus_item + LISTBOX_GetCurrentPageSize(descr) - 1;
        if (caret >= descr->nb_items) caret = descr->nb_items - 1;
        break;
    case VK_HOME:
        caret = 0;
        break;
    case VK_END:
        caret = descr->nb_items - 1;
        break;
    case VK_SPACE:
        if (descr->style & LBS_EXTENDEDSEL) caret = descr->focus_item;
        else if (descr->style & LBS_MULTIPLESEL)
        {
            LISTBOX_SetSelection( descr, descr->focus_item,
                                  !descr->items[descr->focus_item].selected,
                                  (descr->style & LBS_NOTIFY) != 0 );
        }
        break;
    default:
        bForceSelection = FALSE;
    }
    if (bForceSelection) /* focused item is used instead of key */
        caret = descr->focus_item;
    if (caret >= 0)
    {
        if (((descr->style & LBS_EXTENDEDSEL) &&
            !(GetKeyState( VK_SHIFT ) & 0x8000)) ||
            !IS_MULTISELECT(descr))
            descr->anchor_item = caret;
        LISTBOX_MoveCaret( descr, caret, TRUE );

        if (descr->style & LBS_MULTIPLESEL)
            descr->selected_item = caret;
        else
            LISTBOX_SetSelection( descr, caret, TRUE, FALSE);
        if (descr->style & LBS_NOTIFY)
        {
            if (descr->lphc && IsWindowVisible( descr->self ))
            {
                /* make sure that combo parent doesn't hide us */
                descr->lphc->wState |= CBF_NOROLLUP;
            }
            if (descr->nb_items) SEND_NOTIFICATION( descr, LBN_SELCHANGE );
        }
    }
    return 0;
}