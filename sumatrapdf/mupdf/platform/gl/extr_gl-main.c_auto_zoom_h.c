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
struct TYPE_2__ {int h; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXRES ; 
 int /*<<< orphan*/  MINRES ; 
 int canvas_h ; 
 int currentzoom ; 
 int fz_clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ page_tex ; 

__attribute__((used)) static void auto_zoom_h(void)
{
	currentzoom = fz_clamp(currentzoom * canvas_h / page_tex.h, MINRES, MAXRES);
}