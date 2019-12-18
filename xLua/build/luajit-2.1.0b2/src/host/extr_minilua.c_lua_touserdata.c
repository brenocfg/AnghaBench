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
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  index2adr (int /*<<< orphan*/ *,int) ; 
 void* pvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawuvalue (int /*<<< orphan*/ ) ; 
 int ttype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void*lua_touserdata(lua_State*L,int idx){
StkId o=index2adr(L,idx);
switch(ttype(o)){
case 7:return(rawuvalue(o)+1);
case 2:return pvalue(o);
default:return NULL;
}
}