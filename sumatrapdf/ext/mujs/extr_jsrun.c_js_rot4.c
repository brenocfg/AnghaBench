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
typedef  int /*<<< orphan*/  js_Value ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/ * STACK ; 
 int TOP ; 

void js_rot4(js_State *J)
{
	/* A B C D -> D A B C */
	js_Value tmp = STACK[TOP-1];	/* A B C D (D) */
	STACK[TOP-1] = STACK[TOP-2];	/* A B C C */
	STACK[TOP-2] = STACK[TOP-3];	/* A B B C */
	STACK[TOP-3] = STACK[TOP-4];	/* A A B C */
	STACK[TOP-4] = tmp;		/* D A B C */
}