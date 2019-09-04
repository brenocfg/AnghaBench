#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  title ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_CAPTION ; 
 int /*<<< orphan*/  COLOR_TEXT ; 
 int /*<<< orphan*/  ClrLine (int /*<<< orphan*/ ) ; 
 int GLOBAL_SCREEN_WIDTH ; 
 int /*<<< orphan*/  PutChar (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetColor () ; 
 int /*<<< orphan*/  SetBackgroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundColor (int /*<<< orphan*/ ) ; 

void PrintCaption(void)
{
    const char title[]=" PrivateICE system level debugger (REACTOS) ";

    SetForegroundColor(COLOR_TEXT);
	SetBackgroundColor(COLOR_CAPTION);

	ClrLine(0);
	PutChar((LPSTR)title,
		   (GLOBAL_SCREEN_WIDTH-sizeof(title))/2,
           0);

    ResetColor();
}