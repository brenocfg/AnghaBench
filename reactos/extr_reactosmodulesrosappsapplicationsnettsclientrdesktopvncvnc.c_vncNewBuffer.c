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
struct TYPE_4__ {int owner; int w; int h; int linew; TYPE_2__* format; void* data; } ;
typedef  TYPE_1__ vncBuffer ;
struct TYPE_5__ {int bitsPerPixel; } ;

/* Variables and functions */
 TYPE_2__* vncNewFormat (int) ; 
 scalar_t__ xmalloc (int) ; 

vncBuffer *
vncNewBuffer(int w, int h, int depth)
{
	vncBuffer *b = (vncBuffer *) xmalloc(sizeof(vncBuffer));
	b->format = vncNewFormat(depth);
	b->data = (void *) xmalloc(w * h * (b->format->bitsPerPixel / 8));
	b->owner = 1;
	b->w = w;
	b->h = h;
	b->linew = w;
	return b;
}