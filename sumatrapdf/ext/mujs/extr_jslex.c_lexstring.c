#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int lexchar; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int TK_STRING ; 
 scalar_t__ jsY_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsY_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  jsY_expect (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jsY_next (TYPE_1__*) ; 
 int /*<<< orphan*/  js_intern (TYPE_1__*,char const*) ; 
 scalar_t__ lexescape (TYPE_1__*) ; 
 char* textend (TYPE_1__*) ; 
 int /*<<< orphan*/  textinit (TYPE_1__*) ; 
 int /*<<< orphan*/  textpush (TYPE_1__*,char) ; 

__attribute__((used)) static int lexstring(js_State *J)
{
	const char *s;

	int q = J->lexchar;
	jsY_next(J);

	textinit(J);

	while (J->lexchar != q) {
		if (J->lexchar == 0 || J->lexchar == '\n')
			jsY_error(J, "string not terminated");
		if (jsY_accept(J, '\\')) {
			if (lexescape(J))
				jsY_error(J, "malformed escape sequence");
		} else {
			textpush(J, J->lexchar);
			jsY_next(J);
		}
	}
	jsY_expect(J, q);

	s = textend(J);

	J->text = js_intern(J, s);
	return TK_STRING;
}