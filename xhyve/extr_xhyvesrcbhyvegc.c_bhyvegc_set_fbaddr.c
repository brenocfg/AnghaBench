#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bhyvegc {int raw; TYPE_1__* gc_image; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 

void
bhyvegc_set_fbaddr(struct bhyvegc *gc, void *fbaddr)
{
	gc->raw = 1;
	if (gc->gc_image->data && gc->gc_image->data != fbaddr)
		free(gc->gc_image->data);
	gc->gc_image->data = fbaddr;
}