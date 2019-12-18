#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ lookahead; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IDENTIFIER ; 
 scalar_t__ TK_BREAK ; 
 scalar_t__ TK_IDENTIFIER ; 
 int /*<<< orphan*/  jsP_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsP_newstrnode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_next (TYPE_1__*) ; 
 int /*<<< orphan*/  jsY_tokenstring (scalar_t__) ; 

__attribute__((used)) static js_Ast *identifiername(js_State *J)
{
	if (J->lookahead == TK_IDENTIFIER || J->lookahead >= TK_BREAK) {
		js_Ast *a = jsP_newstrnode(J, AST_IDENTIFIER, J->text);
		jsP_next(J);
		return a;
	}
	jsP_error(J, "unexpected token: %s (expected identifier or keyword)", jsY_tokenstring(J->lookahead));
}