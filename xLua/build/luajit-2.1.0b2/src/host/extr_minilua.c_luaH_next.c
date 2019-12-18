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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int sizearray; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ Table ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  cast_num (int) ; 
 int findindex (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  gnode (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * gval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * key2tval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnvalue (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ sizenode (TYPE_1__*) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int luaH_next(lua_State*L,Table*t,StkId key){
int i=findindex(L,t,key);
for(i++;i<t->sizearray;i++){
if(!ttisnil(&t->array[i])){
setnvalue(key,cast_num(i+1));
setobj(L,key+1,&t->array[i]);
return 1;
}
}
for(i-=t->sizearray;i<(int)sizenode(t);i++){
if(!ttisnil(gval(gnode(t,i)))){
setobj(L,key,key2tval(gnode(t,i)));
setobj(L,key+1,gval(gnode(t,i)));
return 1;
}
}
return 0;
}