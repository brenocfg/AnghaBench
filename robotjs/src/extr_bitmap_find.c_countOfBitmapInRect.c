#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UTHashTable ;
struct TYPE_7__ {int width; } ;
typedef  int /*<<< orphan*/  MMRect ;
typedef  int /*<<< orphan*/  MMPoint ;
typedef  TYPE_1__* MMBitmapRef ;

/* Variables and functions */
 int /*<<< orphan*/  ITER_NEXT_POINT (int /*<<< orphan*/ ,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMPointZero ; 
 int /*<<< orphan*/  destroyBadShiftTable (int /*<<< orphan*/ *) ; 
 scalar_t__ findBitmapInRectAt (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initBadShiftTable (int /*<<< orphan*/ *,TYPE_1__*) ; 

size_t countOfBitmapInRect(MMBitmapRef needle, MMBitmapRef haystack,
                           MMRect rect, float tolerance)
{
	size_t count = 0;
	MMPoint point = MMPointZero;
	UTHashTable badShiftTable;

	initBadShiftTable(&badShiftTable, needle);
	while (findBitmapInRectAt(needle, haystack, &point, rect,
	                          tolerance, point, &badShiftTable) == 0) {
		const size_t scanWidth = (haystack->width - needle->width) + 1;
		++count;
		ITER_NEXT_POINT(point, scanWidth, 0);
	}
	destroyBadShiftTable(&badShiftTable);

	return count;
}