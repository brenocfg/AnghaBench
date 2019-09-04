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
struct TYPE_7__ {int sizeupvalues; int sizelocvars; int sizecode; int sizelineinfo; TYPE_2__* locvars; TYPE_1__* upvalues; int /*<<< orphan*/  source; int /*<<< orphan*/ * l_G; } ;
struct TYPE_6__ {int /*<<< orphan*/  varname; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ SharedProto ;
typedef  int /*<<< orphan*/  LocVar ;
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  markobjectN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marksharedproto (global_State *g, SharedProto *f) {
  int i;
  if (g != f->l_G)
    return 0;
  markobjectN(g, f->source);
  for (i = 0; i < f->sizeupvalues; i++)  /* mark upvalue names */
    markobjectN(g, f->upvalues[i].name);
  for (i = 0; i < f->sizelocvars; i++)  /* mark local-variable names */
    markobjectN(g, f->locvars[i].varname);
  return sizeof(Instruction) * f->sizecode +
         sizeof(int) * f->sizelineinfo +
         sizeof(LocVar) * f->sizelocvars +
         sizeof(Upvaldesc) * f->sizeupvalues;
}