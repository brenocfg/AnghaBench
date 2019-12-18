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

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BACKGROUND ; 
 int /*<<< orphan*/  COLOR_FOREGROUND ; 
 int /*<<< orphan*/  SetBackgroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundColor (int /*<<< orphan*/ ) ; 

void ResetColor(void)
{
    SetForegroundColor(COLOR_FOREGROUND);
	SetBackgroundColor(COLOR_BACKGROUND);
}