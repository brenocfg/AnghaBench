#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lookahead; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 scalar_t__ TK_IDENTIFIER ; 
 int /*<<< orphan*/ * identifier (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *identifieropt(js_State *J)
{
	if (J->lookahead == TK_IDENTIFIER)
		return identifier(J);
	return NULL;
}