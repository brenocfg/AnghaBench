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
struct TYPE_3__ {int /*<<< orphan*/  Self; void* MaxVal; void* MinVal; } ;
typedef  TYPE_1__ UPDOWN_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  void* INT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT UPDOWN_SetRange(UPDOWN_INFO *infoPtr, INT Max, INT Min)
{
    infoPtr->MaxVal = Max;
    infoPtr->MinVal = Min;

    TRACE("UpDown Ctrl new range(%d to %d), hwnd=%p\n",
           infoPtr->MinVal, infoPtr->MaxVal, infoPtr->Self);

    return 0;
}