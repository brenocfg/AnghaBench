#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_5__ {scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_2__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DSTINVERT ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PatBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
HEADER_DrawTrackLine (const HEADER_INFO *infoPtr, HDC hdc, INT x)
{
    RECT rect;

    GetClientRect (infoPtr->hwndSelf, &rect);
    PatBlt( hdc, x, rect.top, 1, rect.bottom - rect.top, DSTINVERT );
}