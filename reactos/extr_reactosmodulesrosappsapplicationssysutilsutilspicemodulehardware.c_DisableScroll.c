#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
struct TYPE_2__ {int /*<<< orphan*/  bScrollDisabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* wWindow ; 

void DisableScroll(USHORT Window)
{
    ENTER_FUNC();
	wWindow[Window].bScrollDisabled=TRUE;
    LEAVE_FUNC();
}