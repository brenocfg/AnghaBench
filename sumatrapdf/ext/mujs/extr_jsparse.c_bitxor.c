#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  TYPE_1__* js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  BITXOR ; 
 TYPE_1__** EXP2 (int /*<<< orphan*/ ,TYPE_1__**,TYPE_1__**) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  POPREC () ; 
 int /*<<< orphan*/  SAVEREC () ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 

__attribute__((used)) static js_Ast *bitxor(js_State *J, int notin)
{
	js_Ast *a = bitand(J, notin);
	SAVEREC();
	int line = J->lexline;
	while (jsP_accept(J, '^')) {
		INCREC();
		a = EXP2(BITXOR, a, bitand(J, notin));
		line = J->lexline;
	}
	POPREC();
	return a;
}