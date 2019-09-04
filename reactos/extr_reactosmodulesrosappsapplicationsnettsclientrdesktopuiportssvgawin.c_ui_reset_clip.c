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
 int /*<<< orphan*/  clip_endx ; 
 int /*<<< orphan*/  clip_endy ; 
 scalar_t__ clip_startx ; 
 scalar_t__ clip_starty ; 
 int /*<<< orphan*/  g_height ; 
 int /*<<< orphan*/  g_width ; 

void ui_reset_clip(void)
{
  clip_startx = 0;
  clip_starty = 0;
  clip_endx = g_width;
  clip_endy = g_height;
}