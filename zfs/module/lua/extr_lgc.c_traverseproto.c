#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  global_State ;
typedef  int /*<<< orphan*/  Upvaldesc ;
struct TYPE_7__ {int sizek; int sizeupvalues; int sizep; int sizelocvars; int sizecode; int sizelineinfo; TYPE_2__* locvars; int /*<<< orphan*/ * p; TYPE_1__* upvalues; int /*<<< orphan*/ * k; int /*<<< orphan*/  source; int /*<<< orphan*/ * cache; } ;
struct TYPE_6__ {int /*<<< orphan*/  varname; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_3__ Proto ;
typedef  int /*<<< orphan*/  LocVar ;
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 scalar_t__ iswhite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int traverseproto (global_State *g, Proto *f) {
  int i;
  if (f->cache && iswhite(obj2gco(f->cache)))
    f->cache = NULL;  /* allow cache to be collected */
  markobject(g, f->source);
  for (i = 0; i < f->sizek; i++)  /* mark literals */
    markvalue(g, &f->k[i]);
  for (i = 0; i < f->sizeupvalues; i++)  /* mark upvalue names */
    markobject(g, f->upvalues[i].name);
  for (i = 0; i < f->sizep; i++)  /* mark nested protos */
    markobject(g, f->p[i]);
  for (i = 0; i < f->sizelocvars; i++)  /* mark local-variable names */
    markobject(g, f->locvars[i].varname);
  return sizeof(Proto) + sizeof(Instruction) * f->sizecode +
                         sizeof(Proto *) * f->sizep +
                         sizeof(TValue) * f->sizek +
                         sizeof(int) * f->sizelineinfo +
                         sizeof(LocVar) * f->sizelocvars +
                         sizeof(Upvaldesc) * f->sizeupvalues;
}