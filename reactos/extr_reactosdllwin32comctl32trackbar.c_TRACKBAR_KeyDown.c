#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dwStyle; scalar_t__ lPos; scalar_t__ lRangeMin; scalar_t__ lRangeMax; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  scalar_t__ LONG ;
typedef  int INT ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TBS_DOWNISLEFT ; 
 int TBS_VERT ; 
 int /*<<< orphan*/  TB_BOTTOM ; 
 int /*<<< orphan*/  TB_TOP ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateThumbMove (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRACKBAR_LineDown (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_LineUp (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_PageDown (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_PageUp (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_UpdateThumb (TYPE_1__*) ; 
 int TRUE ; 
#define  VK_DOWN 135 
#define  VK_END 134 
#define  VK_HOME 133 
#define  VK_LEFT 132 
#define  VK_NEXT 131 
#define  VK_PRIOR 130 
#define  VK_RIGHT 129 
#define  VK_UP 128 
 int /*<<< orphan*/  notify_with_scroll (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
TRACKBAR_KeyDown (TRACKBAR_INFO *infoPtr, INT nVirtKey)
{
    BOOL downIsLeft = infoPtr->dwStyle & TBS_DOWNISLEFT;
    BOOL vert = infoPtr->dwStyle & TBS_VERT;
    LONG pos = infoPtr->lPos;

    TRACE("%x\n", nVirtKey);

    switch (nVirtKey) {
    case VK_UP:
	if (!vert && downIsLeft) TRACKBAR_LineDown(infoPtr);
        else TRACKBAR_LineUp(infoPtr);
        break;
    case VK_LEFT:
        if (vert && downIsLeft) TRACKBAR_LineDown(infoPtr);
        else TRACKBAR_LineUp(infoPtr);
        break;
    case VK_DOWN:
	if (!vert && downIsLeft) TRACKBAR_LineUp(infoPtr);
        else TRACKBAR_LineDown(infoPtr);
        break;
    case VK_RIGHT:
	if (vert && downIsLeft) TRACKBAR_LineUp(infoPtr);
        else TRACKBAR_LineDown(infoPtr);
        break;
    case VK_NEXT:
	if (!vert && downIsLeft) TRACKBAR_PageUp(infoPtr);
        else TRACKBAR_PageDown(infoPtr);
        break;
    case VK_PRIOR:
	if (!vert && downIsLeft) TRACKBAR_PageDown(infoPtr);
        else TRACKBAR_PageUp(infoPtr);
        break;
    case VK_HOME:
        if (infoPtr->lPos == infoPtr->lRangeMin) return FALSE;
        infoPtr->lPos = infoPtr->lRangeMin;
        notify_with_scroll (infoPtr, TB_TOP);
        break;
    case VK_END:
        if (infoPtr->lPos == infoPtr->lRangeMax) return FALSE;
        infoPtr->lPos = infoPtr->lRangeMax;
        notify_with_scroll (infoPtr, TB_BOTTOM);
        break;
    }

    if (pos != infoPtr->lPos) {
	TRACKBAR_UpdateThumb (infoPtr);
	TRACKBAR_InvalidateThumbMove (infoPtr, pos, infoPtr->lPos);
    }

    return TRUE;
}