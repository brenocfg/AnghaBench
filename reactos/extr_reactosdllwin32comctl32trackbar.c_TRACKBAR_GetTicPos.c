#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int right; int left; } ;
struct TYPE_6__ {int right; int left; } ;
struct TYPE_8__ {scalar_t__ uNumTics; int lRangeMax; int lRangeMin; TYPE_2__ rcChannel; TYPE_1__ rcThumb; int /*<<< orphan*/  tics; } ;
typedef  TYPE_3__ TRACKBAR_INFO ;
typedef  int LONG ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int TRACKBAR_GetTic (TYPE_3__ const*,scalar_t__) ; 

__attribute__((used)) static inline LONG
TRACKBAR_GetTicPos (const TRACKBAR_INFO *infoPtr, INT iTic)
{
    LONG range, width, pos, tic;
    int offsetthumb;

    if ((iTic < 0) || (iTic >= infoPtr->uNumTics) || !infoPtr->tics)
	return -1;

    tic   = TRACKBAR_GetTic (infoPtr, iTic);
    range = infoPtr->lRangeMax - infoPtr->lRangeMin;
    if (range <= 0) range = 1;
    offsetthumb = (infoPtr->rcThumb.right - infoPtr->rcThumb.left)/2;
    width = infoPtr->rcChannel.right - infoPtr->rcChannel.left - offsetthumb*2;
    pos   = infoPtr->rcChannel.left + offsetthumb + (width * tic) / range;

    return pos;
}