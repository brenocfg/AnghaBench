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
typedef  TYPE_1__* rfbScreenInfoPtr ;
typedef  int /*<<< orphan*/  rfbColourMap ;
struct TYPE_4__ {int /*<<< orphan*/  colourMap; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfbSetClientColourMaps (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vncDeleteColourMap (int /*<<< orphan*/ *) ; 

void
vncSetColourMap(rfbScreenInfoPtr s, rfbColourMap * m)
{
	vncDeleteColourMap(&s->colourMap);
	s->colourMap = *m;
	rfbSetClientColourMaps(s, 0, 0);
}