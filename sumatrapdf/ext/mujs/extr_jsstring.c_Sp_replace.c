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
 int /*<<< orphan*/  Sp_replace_regexp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sp_replace_string (int /*<<< orphan*/ *) ; 
 scalar_t__ js_isregexp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void Sp_replace(js_State *J)
{
	if (js_isregexp(J, 1))
		Sp_replace_regexp(J);
	else
		Sp_replace_string(J);
}