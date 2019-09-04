#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hDC; int /*<<< orphan*/  scrolltheme; } ;
struct TYPE_9__ {scalar_t__ right; scalar_t__ left; scalar_t__ bottom; scalar_t__ top; } ;
struct TYPE_8__ {int* rgstate; } ;
typedef  TYPE_1__ SCROLLBARINFO ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PDRAW_CONTEXT ;

/* Variables and functions */
 scalar_t__ BUTTON_DISABLED ; 
 scalar_t__ BUTTON_HOT ; 
 scalar_t__ BUTTON_NORMAL ; 
 scalar_t__ BUTTON_PRESSED ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int STATE_SYSTEM_UNAVAILABLE ; 

__attribute__((used)) static void SCROLL_ThemeDrawPart(PDRAW_CONTEXT pcontext, int iPartId,int iStateId,  SCROLLBARINFO* psbi, int htCurrent, int htDown, int htHot, RECT* r)
{
    if (r->right <= r->left || r->bottom <= r->top)
        return;

    if(psbi->rgstate[htCurrent] & STATE_SYSTEM_UNAVAILABLE)
        iStateId += BUTTON_DISABLED - BUTTON_NORMAL;
    else if (htHot == htCurrent)
        iStateId += BUTTON_HOT - BUTTON_NORMAL;
    else if (htDown == htCurrent)
        iStateId += BUTTON_PRESSED - BUTTON_NORMAL;

    DrawThemeBackground(pcontext->scrolltheme, pcontext->hDC, iPartId, iStateId, r, NULL);
}