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
typedef  int /*<<< orphan*/  vncBuffer ;
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/ * ui_create_bitmap (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vncCopyBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vncDeleteBuffer (int /*<<< orphan*/ *) ; 

void
ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	vncBuffer *buf;
	buf = ui_create_bitmap(width, height, data);
	vncCopyBlitFrom(server, x, y, cx, cy, buf, 0, 0);
	vncDeleteBuffer(buf);
}