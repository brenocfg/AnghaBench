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
typedef  int /*<<< orphan*/  UTHashTable ;
typedef  int /*<<< orphan*/  MMRect ;
typedef  int /*<<< orphan*/  MMPoint ;
typedef  int /*<<< orphan*/  MMBitmapRef ;

/* Variables and functions */
 int /*<<< orphan*/  MMPointZero ; 
 int /*<<< orphan*/  destroyBadShiftTable (int /*<<< orphan*/ *) ; 
 int findBitmapInRectAt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initBadShiftTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int findBitmapInRect(MMBitmapRef needle,
		             MMBitmapRef haystack,
                     MMPoint *point,
                     MMRect rect,
                     float tolerance)
{
	UTHashTable badShiftTable;
	int ret;

	initBadShiftTable(&badShiftTable, needle);
	ret = findBitmapInRectAt(needle, haystack, point, rect,
	                         tolerance, MMPointZero, &badShiftTable);
	destroyBadShiftTable(&badShiftTable);
	return ret;
}