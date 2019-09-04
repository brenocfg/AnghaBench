#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  int WORD ;
struct TYPE_8__ {int style; int top_item; int nb_items; int /*<<< orphan*/  self; } ;
struct TYPE_7__ {int cbSize; int nTrackPos; int /*<<< orphan*/  fMask; } ;
typedef  TYPE_1__ SCROLLINFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ LB_DESCR ;

/* Variables and functions */
 int /*<<< orphan*/  GetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int LBS_MULTICOLUMN ; 
 int LISTBOX_GetCurrentPageSize (TYPE_2__*) ; 
 int /*<<< orphan*/  LISTBOX_SetTopItem (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
#define  SB_BOTTOM 135 
#define  SB_LINEDOWN 134 
#define  SB_LINEUP 133 
#define  SB_PAGEDOWN 132 
#define  SB_PAGEUP 131 
#define  SB_THUMBPOSITION 130 
#define  SB_THUMBTRACK 129 
#define  SB_TOP 128 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  SIF_TRACKPOS ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT LISTBOX_HandleVScroll( LB_DESCR *descr, WORD scrollReq, WORD pos )
{
    SCROLLINFO info;

    if (descr->style & LBS_MULTICOLUMN) return 0;
    switch(scrollReq)
    {
    case SB_LINEUP:
        LISTBOX_SetTopItem( descr, descr->top_item - 1, TRUE );
        break;
    case SB_LINEDOWN:
        LISTBOX_SetTopItem( descr, descr->top_item + 1, TRUE );
        break;
    case SB_PAGEUP:
        LISTBOX_SetTopItem( descr, descr->top_item -
                            LISTBOX_GetCurrentPageSize( descr ), TRUE );
        break;
    case SB_PAGEDOWN:
        LISTBOX_SetTopItem( descr, descr->top_item +
                            LISTBOX_GetCurrentPageSize( descr ), TRUE );
        break;
    case SB_THUMBPOSITION:
        LISTBOX_SetTopItem( descr, pos, TRUE );
        break;
    case SB_THUMBTRACK:
        info.cbSize = sizeof(info);
        info.fMask = SIF_TRACKPOS;
        GetScrollInfo( descr->self, SB_VERT, &info );
        LISTBOX_SetTopItem( descr, info.nTrackPos, TRUE );
        break;
    case SB_TOP:
        LISTBOX_SetTopItem( descr, 0, TRUE );
        break;
    case SB_BOTTOM:
        LISTBOX_SetTopItem( descr, descr->nb_items, TRUE );
        break;
    }
    return 0;
}