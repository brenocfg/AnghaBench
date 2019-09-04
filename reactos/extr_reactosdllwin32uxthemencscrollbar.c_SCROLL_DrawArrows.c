#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ right; scalar_t__ left; scalar_t__ bottom; scalar_t__ top; } ;
struct TYPE_6__ {scalar_t__ dxyLineButton; TYPE_2__ rcScrollBar; } ;
typedef  TYPE_1__ SCROLLBARINFO ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  PDRAW_CONTEXT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ABS_DOWNNORMAL ; 
 int ABS_LEFTNORMAL ; 
 int ABS_RIGHTNORMAL ; 
 int ABS_UPNORMAL ; 
 int /*<<< orphan*/  SBP_ARROWBTN ; 
 int /*<<< orphan*/  SCROLL_BOTTOM_ARROW ; 
 int /*<<< orphan*/  SCROLL_TOP_ARROW ; 
 int /*<<< orphan*/  SCROLL_ThemeDrawPart (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int,int,TYPE_2__*) ; 

__attribute__((used)) static void SCROLL_DrawArrows( PDRAW_CONTEXT pcontext, SCROLLBARINFO* psbi, 
                               BOOL vertical, int htDown, int htHot )
{
    RECT r;
    int iStateId;

    r = psbi->rcScrollBar;
    if( vertical )
    {
        r.bottom = r.top + psbi->dxyLineButton;
        iStateId = ABS_UPNORMAL;
    }
    else
    {
        r.right = r.left + psbi->dxyLineButton;
        iStateId = ABS_LEFTNORMAL;
    }
    
    SCROLL_ThemeDrawPart(pcontext, SBP_ARROWBTN, iStateId, psbi, SCROLL_TOP_ARROW, htDown, htHot, &r);
    
    r = psbi->rcScrollBar;
    if( vertical )
    {
        r.top = r.bottom - psbi->dxyLineButton;
        iStateId = ABS_DOWNNORMAL;
    }
    else
    {
        iStateId = ABS_RIGHTNORMAL;
        r.left = r.right - psbi->dxyLineButton;
    }

    SCROLL_ThemeDrawPart(pcontext, SBP_ARROWBTN, iStateId, psbi, SCROLL_BOTTOM_ARROW, htDown, htHot, &r);
}