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
typedef  int /*<<< orphan*/  vncPixel ;
struct TYPE_5__ {int linew; scalar_t__ data; TYPE_1__* format; } ;
typedef  TYPE_2__ vncBuffer ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int bitsPerPixel; } ;

/* Variables and functions */

void
vncSetPixel(vncBuffer * b, int x, int y, vncPixel c)
{
	unsigned long offset = (x + (y * (b->linew))) * (b->format->bitsPerPixel >> 3);
	((uint8_t *) (b->data))[offset] = c;
}