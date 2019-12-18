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
 int /*<<< orphan*/  MAXRES ; 
 int /*<<< orphan*/  MINRES ; 
 int canvas_x ; 
 int canvas_y ; 
 int currentzoom ; 
 int fz_clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scroll_x ; 
 int scroll_y ; 

__attribute__((used)) static void set_zoom(int z, int cx, int cy)
{
	z = fz_clamp(z, MINRES, MAXRES);
	scroll_x = (scroll_x + cx - canvas_x) * z / currentzoom - cx + canvas_x;
	scroll_y = (scroll_y + cy - canvas_y) * z / currentzoom - cy + canvas_y;
	currentzoom = z;
}