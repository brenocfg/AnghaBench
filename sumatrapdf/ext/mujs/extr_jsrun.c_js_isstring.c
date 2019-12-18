#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
typedef  enum js_Type { ____Placeholder_js_Type } js_Type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int JS_TLITSTR ; 
 int JS_TMEMSTR ; 
 int JS_TSHRSTR ; 
 TYPE_1__* stackidx (int /*<<< orphan*/ *,int) ; 

int js_isstring(js_State *J, int idx) { enum js_Type t = stackidx(J, idx)->type; return t == JS_TSHRSTR || t == JS_TLITSTR || t == JS_TMEMSTR; }