#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct shiftNode {int dummy; } ;
typedef  int /*<<< orphan*/  UTHashTable ;
struct TYPE_8__ {int width; size_t height; } ;
struct TYPE_7__ {size_t y; int x; } ;
typedef  int /*<<< orphan*/  MMRGBHex ;
typedef  TYPE_1__ MMPoint ;
typedef  TYPE_2__* MMBitmapRef ;

/* Variables and functions */
 TYPE_1__ MMPointMake (int,size_t) ; 
 int /*<<< orphan*/  MMRGBHexAtPoint (TYPE_2__*,int,size_t) ; 
 int /*<<< orphan*/  addNodeToTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  initHashTable (int /*<<< orphan*/ *,size_t const,int) ; 
 int /*<<< orphan*/  tableHasKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initBadShiftTable(UTHashTable *jumpTable, MMBitmapRef needle)
{
	const MMPoint lastPoint = MMPointMake(needle->width - 1, needle->height - 1);
	const size_t maxColors = needle->width * needle->height;
	MMPoint scan;

	/* Allocate max size initially to avoid a million calls to malloc(). */
	initHashTable(jumpTable, maxColors, sizeof(struct shiftNode));

	/* Populate jumpTable with analysis of |needle|. */
	for (scan.y = lastPoint.y; ; --scan.y) {
		for (scan.x = lastPoint.x; ; --scan.x) {
			MMRGBHex color = MMRGBHexAtPoint(needle, scan.x, scan.y);
			if (!tableHasKey(jumpTable, color)) {
				addNodeToTable(jumpTable, color,
				               MMPointMake(needle->width - scan.x,
				                           needle->height - scan.y));
			}

			if (scan.x == 0) break; /* Avoid infinite loop from unsigned type. */
		}
		if (scan.y == 0) break;
	}
}