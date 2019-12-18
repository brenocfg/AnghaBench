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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  GrSetGCRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ g_clip ; 
 int /*<<< orphan*/  g_gc ; 
 int /*<<< orphan*/  g_height ; 
 int /*<<< orphan*/  g_width ; 

void ui_reset_clip(void)
{
  GrSetGCRegion(g_gc, 0);
  g_clip.x = 0;
  g_clip.y = 0;
  g_clip.width = g_width;
  g_clip.height = g_height;
}