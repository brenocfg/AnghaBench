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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int* bytes; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
typedef  TYPE_2__ rfbColourMap ;

/* Variables and functions */
 scalar_t__ abs (int) ; 

uint8_t
vncLookupColour(rfbColourMap * colourMap, uint8_t * p)
{
	uint8_t i, i1 = 0;
	uint8_t *cm = colourMap->data.bytes;
	uint32_t m, m1 = abs(cm[0] - p[0]) + abs(cm[1] - p[1]) + abs(cm[2] - p[2]);
	for (i = 1; i < 255; i++)
	{
		m = abs(cm[i * 3] - p[0]) + abs(cm[i * 3 + 1] - p[1]) + abs(cm[i * 3 + 2] - p[2]);
		if (m < m1)
		{
			m1 = m;
			i1 = i;
		}
	}
	return (i1);
}