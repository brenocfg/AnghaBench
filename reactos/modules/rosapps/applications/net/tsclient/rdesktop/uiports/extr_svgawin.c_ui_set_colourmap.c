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
 void* colmap ; 
 int /*<<< orphan*/  vga_setpalvec (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  xfree (void*) ; 

void ui_set_colourmap(void* map)
{
  if (colmap != 0)
    xfree(colmap);
  vga_setpalvec(0, 256, (int*)map);
  colmap = map;
}