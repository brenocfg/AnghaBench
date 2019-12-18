#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lu_mem ;
struct TYPE_14__ {TYPE_3__* rootgc; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_16__ {int /*<<< orphan*/  openupval; } ;
struct TYPE_13__ {int tt; int marked; TYPE_3__* next; } ;
struct TYPE_15__ {TYPE_1__ gch; } ;
typedef  TYPE_3__ GCObject ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int bit2mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freeobj (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_9__* gco2th (TYPE_3__*) ; 
 int /*<<< orphan*/  makewhite (TYPE_2__*,TYPE_3__*) ; 
 int otherwhite (TYPE_2__*) ; 
 int /*<<< orphan*/  sweepwholelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GCObject**sweeplist(lua_State*L,GCObject**p,lu_mem count){
GCObject*curr;
global_State*g=G(L);
int deadmask=otherwhite(g);
while((curr=*p)!=NULL&&count-->0){
if(curr->gch.tt==8)
sweepwholelist(L,&gco2th(curr)->openupval);
if((curr->gch.marked^bit2mask(0,1))&deadmask){
makewhite(g,curr);
p=&curr->gch.next;
}
else{
*p=curr->gch.next;
if(curr==g->rootgc)
g->rootgc=curr->gch.next;
freeobj(L,curr);
}
}
return p;
}