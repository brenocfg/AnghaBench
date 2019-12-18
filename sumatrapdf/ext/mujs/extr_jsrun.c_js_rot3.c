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

void js_rot3(js_State *J)
{
	/* A B C -> C A B */
	js_Value tmp = STACK[TOP-1];	/* A B C (C) */
	STACK[TOP-1] = STACK[TOP-2];	/* A B B */
	STACK[TOP-2] = STACK[TOP-3];	/* A A B */
	STACK[TOP-3] = tmp;		/* C A B */
}