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
typedef  int /*<<< orphan*/  js_Finalize ;

/* Variables and functions */
 int /*<<< orphan*/  js_newuserdatax (int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void js_newuserdata(js_State *J, const char *tag, void *data, js_Finalize finalize)
{
	js_newuserdatax(J, tag, data, NULL, NULL, NULL, finalize);
}