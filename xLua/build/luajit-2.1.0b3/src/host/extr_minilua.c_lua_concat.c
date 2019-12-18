#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ top; scalar_t__ base; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  api_checknelems (TYPE_1__*,int) ; 
 int /*<<< orphan*/  api_incr_top (TYPE_1__*) ; 
 scalar_t__ cast_int (scalar_t__) ; 
 int /*<<< orphan*/  luaC_checkGC (TYPE_1__*) ; 
 int /*<<< orphan*/  luaS_newlstr (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaV_concat (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  setsvalue (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_concat(lua_State*L,int n){
api_checknelems(L,n);
if(n>=2){
luaC_checkGC(L);
luaV_concat(L,n,cast_int(L->top-L->base)-1);
L->top-=(n-1);
}
else if(n==0){
setsvalue(L,L->top,luaS_newlstr(L,"",0));
api_incr_top(L);
}
}