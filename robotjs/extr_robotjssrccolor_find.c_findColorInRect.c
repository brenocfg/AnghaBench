#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ MMRect ;
typedef  int /*<<< orphan*/  MMRGBHex ;
typedef  int /*<<< orphan*/  MMPoint ;
typedef  int /*<<< orphan*/  MMBitmapRef ;

/* Variables and functions */
 int findColorInRectAt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__,float,int /*<<< orphan*/ ) ; 

int findColorInRect(MMBitmapRef image, MMRGBHex color,
                    MMPoint *point, MMRect rect, float tolerance)
{
	return findColorInRectAt(image, color, point, rect, tolerance, rect.origin);
}