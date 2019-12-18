#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ js_Value ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 scalar_t__ JS_TNULL ; 
 scalar_t__ JS_TUNDEFINED ; 
 TYPE_1__* stackidx (int /*<<< orphan*/ *,int) ; 

int js_iscoercible(js_State *J, int idx) { js_Value *v = stackidx(J, idx); return v->type != JS_TUNDEFINED && v->type != JS_TNULL; }