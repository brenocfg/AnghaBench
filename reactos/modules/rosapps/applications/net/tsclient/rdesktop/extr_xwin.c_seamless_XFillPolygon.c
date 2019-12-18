#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int y; } ;
typedef  TYPE_2__ XPoint ;
struct TYPE_7__ {int /*<<< orphan*/  gc; } ;
struct TYPE_9__ {TYPE_1__ xwin; int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Drawable ;

/* Variables and functions */
 int /*<<< orphan*/  Complex ; 
 int /*<<< orphan*/  CoordModePrevious ; 
 int /*<<< orphan*/  XFillPolygon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
seamless_XFillPolygon(RDPCLIENT * This, Drawable d, XPoint * points, int npoints, int xoffset, int yoffset)
{
	points[0].x -= xoffset;
	points[0].y -= yoffset;
	XFillPolygon(This->display, d, This->xwin.gc, points, npoints, Complex, CoordModePrevious);
	points[0].x += xoffset;
	points[0].y += yoffset;
}