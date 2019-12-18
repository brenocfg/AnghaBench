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
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  vncSetRect (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 scalar_t__ vncwinClipRect (int*,int*,int*,int*) ; 

void
ui_rect(
	       /* dest */ int x, int y, int cx, int cy,
	       /* brush */ int colour)
{
	if (vncwinClipRect(&x, &y, &cx, &cy))
	{
		vncSetRect(server, x, y, cx, cy, colour);
	}
}