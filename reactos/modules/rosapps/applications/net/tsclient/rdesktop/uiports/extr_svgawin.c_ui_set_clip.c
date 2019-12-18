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
 int clip_endx ; 
 int clip_endy ; 
 int clip_startx ; 
 int clip_starty ; 

void ui_set_clip(int x, int y, int cx, int cy)
{
  clip_startx = x;
  clip_starty = y;
  clip_endx = x + cx;
  clip_endy = y + cy;
}