#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lu_mem ;
typedef  int l_mem ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * hash; } ;
struct TYPE_6__ {int gcstate; int totalbytes; int estimate; int /*<<< orphan*/  gcdept; int /*<<< orphan*/  tmudata; int /*<<< orphan*/ ** sweepgc; TYPE_1__ strt; int /*<<< orphan*/  sweepstrgc; int /*<<< orphan*/  gray; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCTM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkSizes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markroot (int /*<<< orphan*/ *) ; 
 int propagatemark (TYPE_2__*) ; 
 int /*<<< orphan*/ ** sweeplist (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  sweepwholelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static l_mem singlestep(lua_State*L){
global_State*g=G(L);
switch(g->gcstate){
case 0:{
markroot(L);
return 0;
}
case 1:{
if(g->gray)
return propagatemark(g);
else{
atomic(L);
return 0;
}
}
case 2:{
lu_mem old=g->totalbytes;
sweepwholelist(L,&g->strt.hash[g->sweepstrgc++]);
if(g->sweepstrgc>=g->strt.size)
g->gcstate=3;
g->estimate-=old-g->totalbytes;
return 10;
}
case 3:{
lu_mem old=g->totalbytes;
g->sweepgc=sweeplist(L,g->sweepgc,40);
if(*g->sweepgc==NULL){
checkSizes(L);
g->gcstate=4;
}
g->estimate-=old-g->totalbytes;
return 40*10;
}
case 4:{
if(g->tmudata){
GCTM(L);
if(g->estimate>100)
g->estimate-=100;
return 100;
}
else{
g->gcstate=0;
g->gcdept=0;
return 0;
}
}
default:return 0;
}
}