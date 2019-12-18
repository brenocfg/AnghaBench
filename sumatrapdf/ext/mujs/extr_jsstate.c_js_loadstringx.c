#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * GE; int /*<<< orphan*/ * E; scalar_t__ strict; scalar_t__ default_strict; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Function ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * jsC_compilescript (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  jsP_freeparse (TYPE_1__*) ; 
 int /*<<< orphan*/ * jsP_parse (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  js_endtry (TYPE_1__*) ; 
 int /*<<< orphan*/  js_newscript (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_throw (TYPE_1__*) ; 
 scalar_t__ js_try (TYPE_1__*) ; 

__attribute__((used)) static void js_loadstringx(js_State *J, const char *filename, const char *source, int iseval)
{
	js_Ast *P;
	js_Function *F;

	if (js_try(J)) {
		jsP_freeparse(J);
		js_throw(J);
	}

	P = jsP_parse(J, filename, source);
	F = jsC_compilescript(J, P, iseval ? J->strict : J->default_strict);
	jsP_freeparse(J);
	js_newscript(J, F, iseval ? (J->strict ? J->E : NULL) : J->GE);

	js_endtry(J);
}