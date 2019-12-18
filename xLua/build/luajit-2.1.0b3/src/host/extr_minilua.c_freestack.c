#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  stacksize; int /*<<< orphan*/  stack; int /*<<< orphan*/  size_ci; int /*<<< orphan*/  base_ci; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  CallInfo ; 
 int /*<<< orphan*/  TValue ; 
 int /*<<< orphan*/  luaM_freearray (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freestack(lua_State*L,lua_State*L1){
luaM_freearray(L,L1->base_ci,L1->size_ci,CallInfo);
luaM_freearray(L,L1->stack,L1->stacksize,TValue);
}