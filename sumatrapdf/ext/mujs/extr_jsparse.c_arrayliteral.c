#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char lookahead; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_10__ {struct TYPE_10__* b; } ;
typedef  TYPE_2__ js_Ast ;

/* Variables and functions */
 void* LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arrayelement (TYPE_1__*) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 TYPE_2__* jsP_list (TYPE_2__*) ; 

__attribute__((used)) static js_Ast *arrayliteral(js_State *J)
{
	js_Ast *head, *tail;
	if (J->lookahead == ']')
		return NULL;
	head = tail = LIST(arrayelement(J));
	while (jsP_accept(J, ',')) {
		if (J->lookahead != ']')
			tail = tail->b = LIST(arrayelement(J));
	}
	return jsP_list(head);
}