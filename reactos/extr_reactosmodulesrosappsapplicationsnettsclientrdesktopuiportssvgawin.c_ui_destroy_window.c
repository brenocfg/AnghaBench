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
 int /*<<< orphan*/  TEXT ; 
 int /*<<< orphan*/  keyboard_close () ; 
 scalar_t__ sdata ; 
 int /*<<< orphan*/  vga_setmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

void ui_destroy_window(void)
{
  keyboard_close(); /* Don't forget this! */
  vga_setmode(TEXT);
  if (sdata != 0)
    xfree(sdata);
}