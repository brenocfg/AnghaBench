#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACKBAR_CalcThumb (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
TRACKBAR_InvalidateThumb (const TRACKBAR_INFO *infoPtr, LONG thumbPos)
{
    RECT rcThumb;

    TRACKBAR_CalcThumb(infoPtr, thumbPos, &rcThumb);
    InflateRect(&rcThumb, 1, 1);
    InvalidateRect(infoPtr->hwndSelf, &rcThumb, FALSE);
}