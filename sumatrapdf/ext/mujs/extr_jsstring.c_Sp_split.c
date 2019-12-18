#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  Sp_split_regexp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sp_split_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_isregexp (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Sp_split(js_State *J)
{
	if (js_isundefined(J, 1)) {
		js_newarray(J);
		js_copy(J, 0);
		js_setindex(J, -2, 0);
	} else if (js_isregexp(J, 1)) {
		Sp_split_regexp(J);
	} else {
		Sp_split_string(J);
	}
}