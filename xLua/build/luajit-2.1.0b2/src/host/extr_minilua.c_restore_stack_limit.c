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
struct TYPE_4__ {int size_ci; scalar_t__ base_ci; scalar_t__ ci; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int cast_int (scalar_t__) ; 
 int /*<<< orphan*/  luaD_reallocCI (TYPE_1__*,int) ; 

__attribute__((used)) static void restore_stack_limit(lua_State*L){
if(L->size_ci>20000){
int inuse=cast_int(L->ci-L->base_ci);
if(inuse+1<20000)
luaD_reallocCI(L,20000);
}
}