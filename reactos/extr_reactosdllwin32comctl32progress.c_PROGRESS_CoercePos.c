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
struct TYPE_3__ {scalar_t__ CurVal; scalar_t__ MinVal; scalar_t__ MaxVal; } ;
typedef  TYPE_1__ PROGRESS_INFO ;

/* Variables and functions */

__attribute__((used)) static void PROGRESS_CoercePos(PROGRESS_INFO *infoPtr)
{
    if(infoPtr->CurVal < infoPtr->MinVal)
        infoPtr->CurVal = infoPtr->MinVal;
    if(infoPtr->CurVal > infoPtr->MaxVal)
        infoPtr->CurVal = infoPtr->MaxVal;
}