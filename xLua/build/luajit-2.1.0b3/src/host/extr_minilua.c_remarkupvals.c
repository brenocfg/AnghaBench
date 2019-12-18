#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* next; } ;
struct TYPE_9__ {TYPE_1__ l; } ;
struct TYPE_11__ {int /*<<< orphan*/  v; TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_4__ uvhead; } ;
typedef  TYPE_3__ global_State ;
typedef  TYPE_4__ UpVal ;

/* Variables and functions */
 scalar_t__ isgray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markvalue (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj2gco (TYPE_4__*) ; 

__attribute__((used)) static void remarkupvals(global_State*g){
UpVal*uv;
for(uv=g->uvhead.u.l.next;uv!=&g->uvhead;uv=uv->u.l.next){
if(isgray(obj2gco(uv)))
markvalue(g,uv->v);
}
}