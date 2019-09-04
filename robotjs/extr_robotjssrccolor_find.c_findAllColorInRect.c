#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  x; } ;
struct TYPE_6__ {int /*<<< orphan*/  width; } ;
struct TYPE_8__ {TYPE_2__ origin; TYPE_1__ size; } ;
typedef  TYPE_3__ MMRect ;
typedef  int /*<<< orphan*/  MMRGBHex ;
typedef  int /*<<< orphan*/  MMPointArrayRef ;
typedef  int /*<<< orphan*/  MMPoint ;
typedef  int /*<<< orphan*/  MMBitmapRef ;

/* Variables and functions */
 int /*<<< orphan*/  ITER_NEXT_POINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMPointArrayAppendPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMPointZero ; 
 int /*<<< orphan*/  createMMPointArray (int /*<<< orphan*/ ) ; 
 scalar_t__ findColorInRectAt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__,float,int /*<<< orphan*/ ) ; 

MMPointArrayRef findAllColorInRect(MMBitmapRef image, MMRGBHex color,
                                   MMRect rect, float tolerance)
{
	MMPointArrayRef pointArray = createMMPointArray(0);
	MMPoint point = MMPointZero;

	while (findColorInRectAt(image, color, &point, rect, tolerance, point) == 0) {
		MMPointArrayAppendPoint(pointArray, point);
		ITER_NEXT_POINT(point, rect.size.width, rect.origin.x);
	}

	return pointArray;
}