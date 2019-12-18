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
typedef  void* vncPixel ;
struct TYPE_4__ {void** bytes; } ;
struct TYPE_5__ {int count; TYPE_1__ data; } ;
typedef  TYPE_2__ rfbColourMap ;

/* Variables and functions */

void
vncSetColourMapEntry(rfbColourMap * m, int i, vncPixel r, vncPixel g, vncPixel b)
{
	if (i < m->count)
	{
		m->data.bytes[3 * i + 0] = r;
		m->data.bytes[3 * i + 1] = g;
		m->data.bytes[3 * i + 2] = b;
	}
}