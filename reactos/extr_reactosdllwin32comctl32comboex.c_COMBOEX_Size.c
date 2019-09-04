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
struct TYPE_4__ {int /*<<< orphan*/  hwndCombo; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ COMBOEX_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  COMBOEX_AdjustEditPos (TYPE_1__*) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT COMBOEX_Size (COMBOEX_INFO *infoPtr, INT width, INT height)
{
    TRACE("(width=%d, height=%d)\n", width, height);

    MoveWindow (infoPtr->hwndCombo, 0, 0, width, height, TRUE);

    COMBOEX_AdjustEditPos (infoPtr);

    return 0;
}