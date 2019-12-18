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
struct TYPE_4__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int TK_BREAK ; 
 int TK_IDENTIFIER ; 
 int jsY_findword (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_intern (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * keywords ; 
 int /*<<< orphan*/  nelem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jsY_findkeyword(js_State *J, const char *s)
{
	int i = jsY_findword(s, keywords, nelem(keywords));
	if (i >= 0) {
		J->text = keywords[i];
		return TK_BREAK + i; /* first keyword + i */
	}
	J->text = js_intern(J, s);
	return TK_IDENTIFIER;
}