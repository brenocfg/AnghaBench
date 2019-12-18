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
typedef  int /*<<< orphan*/  Resub ;
typedef  int /*<<< orphan*/  Reprog ;

/* Variables and functions */
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*) ; 
 int js_regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int js_doregexec(js_State *J, Reprog *prog, const char *string, Resub *sub, int eflags)
{
	int result = js_regexec(prog, string, sub, eflags);
	if (result < 0)
		js_error(J, "regexec failed");
	return result;
}