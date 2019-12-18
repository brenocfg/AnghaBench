#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_5__ {struct TYPE_5__* b; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 void* LIST (int /*<<< orphan*/ ) ; 
 scalar_t__ jsP_accept (int /*<<< orphan*/ *,char) ; 
 TYPE_1__* jsP_list (TYPE_1__*) ; 
 int /*<<< orphan*/  vardec (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static js_Ast *vardeclist(js_State *J, int notin)
{
	js_Ast *head, *tail;
	head = tail = LIST(vardec(J, notin));
	while (jsP_accept(J, ','))
		tail = tail->b = LIST(vardec(J, notin));
	return jsP_list(head);
}