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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 void* ui_create_bitmap (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_destroy_bitmap (void*) ; 
 int /*<<< orphan*/  ui_memblt (int,int,int,int,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ui_paint_bitmap(int x, int y, int cx, int cy,
                     int width, int height, uint8 * data)
{
  void * b;

  b = ui_create_bitmap(width, height, data);
  ui_memblt(12, x, y, cx, cy, b, 0, 0);
  ui_destroy_bitmap(b);
}