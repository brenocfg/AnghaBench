#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  calbutton; int /*<<< orphan*/  hwndSelf; scalar_t__ bCalDepressed; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
DATETIME_LButtonUp (DATETIME_INFO *infoPtr)
{
    if(infoPtr->bCalDepressed) {
        infoPtr->bCalDepressed = FALSE;
        InvalidateRect(infoPtr->hwndSelf, &(infoPtr->calbutton), TRUE);
    }

    return 0;
}