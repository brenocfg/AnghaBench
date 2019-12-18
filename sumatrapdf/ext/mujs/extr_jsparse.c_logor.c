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
struct TYPE_5__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  DECREC () ; 
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  LOGOR ; 
 int /*<<< orphan*/  TK_OR ; 
 scalar_t__ jsP_accept (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * logand (TYPE_1__*,int) ; 

__attribute__((used)) static js_Ast *logor(js_State *J, int notin)
{
	js_Ast *a = logand(J, notin);
	int line = J->lexline;
	if (jsP_accept(J, TK_OR)) {
		INCREC();
		a = EXP2(LOGOR, a, logor(J, notin));
		DECREC();
	}
	return a;
}