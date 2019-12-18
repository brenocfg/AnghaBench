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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  cast_num (int) ; 
 int /*<<< orphan*/ * gnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* gval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key2tval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* luaH_getnum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  const* luaH_getstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const luaO_nilobject_ ; 
 int /*<<< orphan*/  luaO_rawequalObj (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lua_number2int (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_numeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mainposition (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rawtsvalue (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const TValue*luaH_get(Table*t,const TValue*key){
switch(ttype(key)){
case 0:return(&luaO_nilobject_);
case 4:return luaH_getstr(t,rawtsvalue(key));
case 3:{
int k;
lua_Number n=nvalue(key);
lua_number2int(k,n);
if(luai_numeq(cast_num(k),nvalue(key)))
return luaH_getnum(t,k);
}
default:{
Node*n=mainposition(t,key);
do{
if(luaO_rawequalObj(key2tval(n),key))
return gval(n);
else n=gnext(n);
}while(n);
return(&luaO_nilobject_);
}
}
}