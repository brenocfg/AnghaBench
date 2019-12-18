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
struct TYPE_4__ {int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/ * jsS_insert (TYPE_1__*,int /*<<< orphan*/ *,char const*,char const**) ; 
 int /*<<< orphan*/  jsS_sentinel ; 

const char *js_intern(js_State *J, const char *s)
{
	const char *result;
	if (!J->strings)
		J->strings = &jsS_sentinel;
	J->strings = jsS_insert(J, J->strings, s, &result);
	return result;
}