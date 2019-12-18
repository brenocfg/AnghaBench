#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_33__ {int stacksize; int size_ci; TYPE_8__* gclist; } ;
typedef  TYPE_4__ lua_State ;
typedef  int l_mem ;
struct TYPE_34__ {TYPE_8__* gray; TYPE_8__* grayagain; } ;
typedef  TYPE_5__ global_State ;
struct TYPE_35__ {int sizearray; TYPE_8__* gclist; } ;
typedef  TYPE_6__ Table ;
struct TYPE_32__ {int /*<<< orphan*/  nupvalues; } ;
struct TYPE_31__ {int /*<<< orphan*/  nupvalues; int /*<<< orphan*/  isC; TYPE_8__* gclist; } ;
struct TYPE_38__ {TYPE_3__ l; TYPE_2__ c; } ;
struct TYPE_30__ {int tt; } ;
struct TYPE_37__ {TYPE_1__ gch; } ;
struct TYPE_36__ {int sizecode; int sizep; int sizek; int sizelineinfo; int sizelocvars; int sizeupvalues; TYPE_8__* gclist; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_7__ Proto ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  LocVar ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  TYPE_8__ GCObject ;
typedef  TYPE_9__ Closure ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  black2gray (TYPE_8__*) ; 
 TYPE_9__* gco2cl (TYPE_8__*) ; 
 TYPE_6__* gco2h (TYPE_8__*) ; 
 TYPE_7__* gco2p (TYPE_8__*) ; 
 TYPE_4__* gco2th (TYPE_8__*) ; 
 int /*<<< orphan*/  gray2black (TYPE_8__*) ; 
 int sizeCclosure (int /*<<< orphan*/ ) ; 
 int sizeLclosure (int /*<<< orphan*/ ) ; 
 int sizenode (TYPE_6__*) ; 
 int /*<<< orphan*/  traverseclosure (TYPE_5__*,TYPE_9__*) ; 
 int /*<<< orphan*/  traverseproto (TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  traversestack (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  traversetable (TYPE_5__*,TYPE_6__*) ; 

__attribute__((used)) static l_mem propagatemark(global_State*g){
GCObject*o=g->gray;
gray2black(o);
switch(o->gch.tt){
case 5:{
Table*h=gco2h(o);
g->gray=h->gclist;
if(traversetable(g,h))
black2gray(o);
return sizeof(Table)+sizeof(TValue)*h->sizearray+
sizeof(Node)*sizenode(h);
}
case 6:{
Closure*cl=gco2cl(o);
g->gray=cl->c.gclist;
traverseclosure(g,cl);
return(cl->c.isC)?sizeCclosure(cl->c.nupvalues):
sizeLclosure(cl->l.nupvalues);
}
case 8:{
lua_State*th=gco2th(o);
g->gray=th->gclist;
th->gclist=g->grayagain;
g->grayagain=o;
black2gray(o);
traversestack(g,th);
return sizeof(lua_State)+sizeof(TValue)*th->stacksize+
sizeof(CallInfo)*th->size_ci;
}
case(8+1):{
Proto*p=gco2p(o);
g->gray=p->gclist;
traverseproto(g,p);
return sizeof(Proto)+sizeof(Instruction)*p->sizecode+
sizeof(Proto*)*p->sizep+
sizeof(TValue)*p->sizek+
sizeof(int)*p->sizelineinfo+
sizeof(LocVar)*p->sizelocvars+
sizeof(TString*)*p->sizeupvalues;
}
default:return 0;
}
}