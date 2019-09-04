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
struct TYPE_4__ {int /*<<< orphan*/  bFocussed; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateAll (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
TRACKBAR_SetFocus (TRACKBAR_INFO *infoPtr)
{
    TRACE("\n");
    infoPtr->bFocussed = TRUE;
    TRACKBAR_InvalidateAll(infoPtr);

    return 0;
}