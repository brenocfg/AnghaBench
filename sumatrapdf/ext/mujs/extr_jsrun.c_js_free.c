#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  actx; int /*<<< orphan*/  (* alloc ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void js_free(js_State *J, void *ptr)
{
	J->alloc(J->actx, ptr, 0);
}