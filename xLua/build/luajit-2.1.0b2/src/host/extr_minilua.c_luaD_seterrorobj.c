#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  luaS_newliteral (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  setsvalue (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void luaD_seterrorobj(lua_State*L,int errcode,StkId oldtop){
switch(errcode){
case 4:{
setsvalue(L,oldtop,luaS_newliteral(L,"not enough memory"));
break;
}
case 5:{
setsvalue(L,oldtop,luaS_newliteral(L,"error in error handling"));
break;
}
case 3:
case 2:{
setobj(L,oldtop,L->top-1);
break;
}
}
L->top=oldtop+1;
}