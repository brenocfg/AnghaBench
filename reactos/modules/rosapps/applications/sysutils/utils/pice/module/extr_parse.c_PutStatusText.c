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
struct TYPE_2__ {scalar_t__ y; } ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ClrLine (scalar_t__) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PutChar (int /*<<< orphan*/ ,int,scalar_t__) ; 
 TYPE_1__* wWindow ; 

void PutStatusText(LPSTR p)
{
    ENTER_FUNC();

	ClrLine(wWindow[OUTPUT_WINDOW].y-1);
	PutChar(p,1,wWindow[OUTPUT_WINDOW].y-1);

    LEAVE_FUNC();
}