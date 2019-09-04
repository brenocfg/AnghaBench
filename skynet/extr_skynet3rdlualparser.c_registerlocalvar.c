#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * varname; } ;
struct TYPE_11__ {size_t nlocvars; TYPE_2__* f; } ;
struct TYPE_10__ {int /*<<< orphan*/  L; TYPE_4__* fs; } ;
struct TYPE_9__ {TYPE_1__* sp; } ;
struct TYPE_8__ {int sizelocvars; TYPE_6__* locvars; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ SharedProto ;
typedef  TYPE_2__ Proto ;
typedef  TYPE_3__ LexState ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  LocVar ; 
 int /*<<< orphan*/  SHRT_MAX ; 
 int /*<<< orphan*/  luaC_objbarrier (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaM_growvector (int /*<<< orphan*/ ,TYPE_6__*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int registerlocalvar (LexState *ls, TString *varname) {
  FuncState *fs = ls->fs;
  Proto *fp = fs->f;
  SharedProto *f = fp->sp;
  int oldsize = f->sizelocvars;
  luaM_growvector(ls->L, f->locvars, fs->nlocvars, f->sizelocvars,
                  LocVar, SHRT_MAX, "local variables");
  while (oldsize < f->sizelocvars)
    f->locvars[oldsize++].varname = NULL;
  f->locvars[fs->nlocvars].varname = varname;
  luaC_objbarrier(ls->L, fp, varname);
  return fs->nlocvars++;
}