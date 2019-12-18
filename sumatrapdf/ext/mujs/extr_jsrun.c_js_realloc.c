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
struct TYPE_4__ {int /*<<< orphan*/  actx; void* (* alloc ) (int /*<<< orphan*/ ,void*,int) ;} ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  js_outofmemory (TYPE_1__*) ; 
 void* stub1 (int /*<<< orphan*/ ,void*,int) ; 

void *js_realloc(js_State *J, void *ptr, int size)
{
	ptr = J->alloc(J->actx, ptr, size);
	if (!ptr)
		js_outofmemory(J);
	return ptr;
}