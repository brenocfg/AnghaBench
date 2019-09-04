#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  info; } ;
struct TYPE_14__ {scalar_t__ k; TYPE_1__ u; } ;
typedef  TYPE_3__ expdesc ;
struct TYPE_18__ {int instack; int /*<<< orphan*/ * name; int /*<<< orphan*/  idx; } ;
struct TYPE_17__ {int nups; TYPE_2__* ls; TYPE_5__* f; } ;
struct TYPE_16__ {TYPE_4__* sp; } ;
struct TYPE_15__ {int sizeupvalues; TYPE_9__* upvalues; } ;
struct TYPE_13__ {int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_4__ SharedProto ;
typedef  TYPE_5__ Proto ;
typedef  TYPE_6__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  MAXUPVAL ; 
 int /*<<< orphan*/  Upvaldesc ; 
 scalar_t__ VLOCAL ; 
 int /*<<< orphan*/  cast_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checklimit (TYPE_6__*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  luaC_objbarrier (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaM_growvector (int /*<<< orphan*/ ,TYPE_9__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int newupvalue (FuncState *fs, TString *name, expdesc *v) {
  Proto *fp = fs->f;
  SharedProto *f = fp->sp;
  int oldsize = f->sizeupvalues;
  checklimit(fs, fs->nups + 1, MAXUPVAL, "upvalues");
  luaM_growvector(fs->ls->L, f->upvalues, fs->nups, f->sizeupvalues,
                  Upvaldesc, MAXUPVAL, "upvalues");
  while (oldsize < f->sizeupvalues)
    f->upvalues[oldsize++].name = NULL;
  f->upvalues[fs->nups].instack = (v->k == VLOCAL);
  f->upvalues[fs->nups].idx = cast_byte(v->u.info);
  f->upvalues[fs->nups].name = name;
  luaC_objbarrier(fs->ls->L, fp, name);
  return fs->nups++;
}