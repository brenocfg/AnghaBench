#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rfbColourMap ;
struct TYPE_5__ {int ncolours; TYPE_1__* colours; } ;
struct TYPE_4__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  int /*<<< orphan*/ * HCOLOURMAP ;
typedef  TYPE_2__ COLOURMAP ;

/* Variables and functions */
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/ * vncNewColourMap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vncSetColourMapEntry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HCOLOURMAP
ui_create_colourmap(COLOURMAP * colours)
{
	int i;
	rfbColourMap *map = vncNewColourMap(server, colours->ncolours);
	for (i = 0; i < colours->ncolours; i++)
	{
		vncSetColourMapEntry(map, i, colours->colours[i].red,
				     colours->colours[i].green, colours->colours[i].blue);
	}
	return map;
}