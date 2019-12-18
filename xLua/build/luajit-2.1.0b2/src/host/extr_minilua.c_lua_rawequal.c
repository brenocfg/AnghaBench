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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/ * StkId ;

/* Variables and functions */
 int /*<<< orphan*/ * index2adr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaO_nilobject_ ; 
 int luaO_rawequalObj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lua_rawequal(lua_State*L,int index1,int index2){
StkId o1=index2adr(L,index1);
StkId o2=index2adr(L,index2);
return(o1==(&luaO_nilobject_)||o2==(&luaO_nilobject_))?0
:luaO_rawequalObj(o1,o2);
}