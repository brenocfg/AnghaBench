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
typedef  int /*<<< orphan*/  lf ;
struct TYPE_7__ {int /*<<< orphan*/  lfWeight; } ;
struct TYPE_6__ {int nCurrentTool; void* hTitleFont; void* hFont; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ LOGFONTW ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 void* CreateFontIndirectW (TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteObject (void*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  FW_BOLD ; 
 int /*<<< orphan*/  GetObjectW (int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_SetFont (TOOLTIPS_INFO *infoPtr, HFONT hFont, BOOL redraw)
{
    LOGFONTW lf;

    if(!GetObjectW(hFont, sizeof(lf), &lf))
        return 0;

    DeleteObject (infoPtr->hFont);
    infoPtr->hFont = CreateFontIndirectW(&lf);

    DeleteObject (infoPtr->hTitleFont);
    lf.lfWeight = FW_BOLD;
    infoPtr->hTitleFont = CreateFontIndirectW(&lf);

    if (redraw && infoPtr->nCurrentTool != -1)
        FIXME("full redraw needed\n");

    return 0;
}