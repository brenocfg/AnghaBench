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
 int ttype (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lua_type(lua_State*L,int idx){
StkId o=index2adr(L,idx);
return(o==(&luaO_nilobject_))?(-1):ttype(o);
}