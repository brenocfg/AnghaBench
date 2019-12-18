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
struct TYPE_4__ {scalar_t__ bytes; } ;
struct TYPE_5__ {scalar_t__ count; TYPE_1__ data; } ;
typedef  TYPE_2__ rfbColourMap ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

void
vncDeleteColourMap(rfbColourMap * m)
{
	if (m->data.bytes)
		free(m->data.bytes);
	m->count = 0;
}