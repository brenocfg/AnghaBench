#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {TYPE_4__ clip_rectangle; int /*<<< orphan*/  gc; } ;
struct TYPE_6__ {TYPE_1__ xwin; int /*<<< orphan*/  display; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XSetClipRectangles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YXBanded ; 

void
ui_reset_clip(RDPCLIENT * This)
{
	This->xwin.clip_rectangle.x = 0;
	This->xwin.clip_rectangle.y = 0;
	This->xwin.clip_rectangle.width = This->width;
	This->xwin.clip_rectangle.height = This->height;
	XSetClipRectangles(This->display, This->xwin.gc, 0, 0, &This->xwin.clip_rectangle, 1, YXBanded);
}