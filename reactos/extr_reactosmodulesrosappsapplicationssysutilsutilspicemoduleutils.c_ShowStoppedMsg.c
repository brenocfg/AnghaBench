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
struct TYPE_2__ {scalar_t__ cy; scalar_t__ y; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_CAPTION ; 
 int /*<<< orphan*/  COLOR_TEXT ; 
 int /*<<< orphan*/  ClrLine (scalar_t__) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PutChar (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ResetColor () ; 
 int /*<<< orphan*/  SetBackgroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundColor (int /*<<< orphan*/ ) ; 
 TYPE_1__* wWindow ; 

void ShowStoppedMsg(void)
{
    ENTER_FUNC();

    SetForegroundColor(COLOR_TEXT);
	SetBackgroundColor(COLOR_CAPTION);
	ClrLine(wWindow[OUTPUT_WINDOW].y+wWindow[OUTPUT_WINDOW].cy);
	PutChar(" Stopped... (Type 'x' to continue) ",1,wWindow[OUTPUT_WINDOW].y+wWindow[OUTPUT_WINDOW].cy);
    ResetColor();

    LEAVE_FUNC();
}