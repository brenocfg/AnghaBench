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
struct TYPE_3__ {scalar_t__ type; struct TYPE_3__* b; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 scalar_t__ AST_LIST ; 
 int /*<<< orphan*/  COMMA ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  comma () ; 
 int /*<<< orphan*/  pexpi (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pargs(int d, js_Ast *list)
{
	while (list) {
		assert(list->type == AST_LIST);
		pexpi(d, COMMA, list->a);
		list = list->b;
		if (list)
			comma();
	}
}