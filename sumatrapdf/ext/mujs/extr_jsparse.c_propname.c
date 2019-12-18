#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ lookahead; int /*<<< orphan*/  text; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_NUMBER ; 
 int /*<<< orphan*/  EXP_STRING ; 
 scalar_t__ TK_NUMBER ; 
 scalar_t__ TK_STRING ; 
 int /*<<< orphan*/ * identifiername (TYPE_1__*) ; 
 int /*<<< orphan*/ * jsP_newnumnode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsP_newstrnode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_next (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *propname(js_State *J)
{
	js_Ast *name;
	if (J->lookahead == TK_NUMBER) {
		name = jsP_newnumnode(J, EXP_NUMBER, J->number);
		jsP_next(J);
	} else if (J->lookahead == TK_STRING) {
		name = jsP_newstrnode(J, EXP_STRING, J->text);
		jsP_next(J);
	} else {
		name = identifiername(J);
	}
	return name;
}