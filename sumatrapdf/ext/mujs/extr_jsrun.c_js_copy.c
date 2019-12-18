#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSTACK (int) ; 
 int /*<<< orphan*/ * STACK ; 
 size_t TOP ; 
 int /*<<< orphan*/ * stackidx (int /*<<< orphan*/ *,int) ; 

void js_copy(js_State *J, int idx)
{
	CHECKSTACK(1);
	STACK[TOP] = *stackidx(J, idx);
	++TOP;
}