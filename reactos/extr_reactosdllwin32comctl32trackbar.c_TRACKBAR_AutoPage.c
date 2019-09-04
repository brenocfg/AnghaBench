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
struct TYPE_8__ {scalar_t__ lPos; int flags; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  POINT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int TB_AUTO_PAGE_LEFT ; 
 int TB_AUTO_PAGE_RIGHT ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TRACKBAR_GetAutoPageDirection (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateThumbMove (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRACKBAR_PageDown (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_PageUp (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_UpdateThumb (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wine_dbgstr_point (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
TRACKBAR_AutoPage (TRACKBAR_INFO *infoPtr, POINT clickPoint)
{
    LONG dir = TRACKBAR_GetAutoPageDirection(infoPtr, clickPoint);
    LONG prevPos = infoPtr->lPos;

    TRACE("clickPoint=%s, dir=%d\n", wine_dbgstr_point(&clickPoint), dir);

    if (dir > 0 && (infoPtr->flags & TB_AUTO_PAGE_RIGHT))
	TRACKBAR_PageDown(infoPtr);
    else if (dir < 0 && (infoPtr->flags & TB_AUTO_PAGE_LEFT))
	TRACKBAR_PageUp(infoPtr);
    else return FALSE;

    TRACKBAR_UpdateThumb (infoPtr);
    TRACKBAR_InvalidateThumbMove (infoPtr, prevPos, infoPtr->lPos);

    return TRUE;
}