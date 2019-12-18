#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_9__ {scalar_t__ x; } ;
struct TYPE_10__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_11__ {TYPE_1__ origin; TYPE_2__ size; } ;
typedef  TYPE_3__ MMRect ;
typedef  int /*<<< orphan*/  MMRGBHex ;
typedef  TYPE_4__ MMPoint ;
typedef  int /*<<< orphan*/  MMBitmapRef ;

/* Variables and functions */
 int /*<<< orphan*/  MMBitmapRectInBounds (int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  MMRGBHexAtPoint (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ MMRGBHexSimilarToColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static int findColorInRectAt(MMBitmapRef image, MMRGBHex color, MMPoint *point,
                             MMRect rect, float tolerance, MMPoint startPoint)
{
	MMPoint scan = startPoint;
	if (!MMBitmapRectInBounds(image, rect)) return -1;

	for (; scan.y < rect.size.height; ++scan.y) {
		for (; scan.x < rect.size.width; ++scan.x) {
			MMRGBHex found = MMRGBHexAtPoint(image, scan.x, scan.y);
			if (MMRGBHexSimilarToColor(color, found, tolerance)) {
				if (point != NULL) *point = scan;
				return 0;
			}
		}
		scan.x = rect.origin.x;
	}

	return -1;
}