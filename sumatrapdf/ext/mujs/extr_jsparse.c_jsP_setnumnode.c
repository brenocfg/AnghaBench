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
struct TYPE_3__ {double number; int /*<<< orphan*/ * d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_NUMBER ; 

__attribute__((used)) static int jsP_setnumnode(js_Ast *node, double x)
{
	node->type = EXP_NUMBER;
	node->number = x;
	node->a = node->b = node->c = node->d = NULL;
	return 1;
}