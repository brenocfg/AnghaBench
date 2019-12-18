#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* gcast; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_8__ {int /*<<< orphan*/  jumps; struct TYPE_8__* gcnext; } ;
typedef  TYPE_2__ js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  jsP_freejumps (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_free (TYPE_1__*,TYPE_2__*) ; 

void jsP_freeparse(js_State *J)
{
	js_Ast *node = J->gcast;
	while (node) {
		js_Ast *next = node->gcnext;
		jsP_freejumps(J, node->jumps);
		js_free(J, node);
		node = next;
	}
	J->gcast = NULL;
}