#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ k; } ;
struct LHS_assign {TYPE_5__ v; struct LHS_assign* prev; } ;
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_20__ {scalar_t__ freereg; } ;
struct TYPE_18__ {TYPE_6__* fs; TYPE_1__* L; } ;
struct TYPE_17__ {scalar_t__ nCcalls; } ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  LUAI_MAXCCALLS ; 
 scalar_t__ VINDEXED ; 
 int /*<<< orphan*/  VNONRELOC ; 
 int /*<<< orphan*/  adjust_assign (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_condition (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_conflict (TYPE_2__*,struct LHS_assign*,TYPE_5__*) ; 
 int /*<<< orphan*/  checklimit (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  checknext (TYPE_2__*,char) ; 
 int explist (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  luaK_setoneret (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_storevar (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suffixedexp (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ testnext (TYPE_2__*,char) ; 
 int /*<<< orphan*/  vkisvar (scalar_t__) ; 

__attribute__((used)) static void assignment (LexState *ls, struct LHS_assign *lh, int nvars) {
  expdesc e;
  check_condition(ls, vkisvar(lh->v.k), "syntax error");
  if (testnext(ls, ',')) {  /* assignment -> ',' suffixedexp assignment */
    struct LHS_assign nv;
    nv.prev = lh;
    suffixedexp(ls, &nv.v);
    if (nv.v.k != VINDEXED)
      check_conflict(ls, lh, &nv.v);
    checklimit(ls->fs, nvars + ls->L->nCcalls, LUAI_MAXCCALLS,
                    "C levels");
    assignment(ls, &nv, nvars+1);
  }
  else {  /* assignment -> '=' explist */
    int nexps;
    checknext(ls, '=');
    nexps = explist(ls, &e);
    if (nexps != nvars)
      adjust_assign(ls, nvars, nexps, &e);
    else {
      luaK_setoneret(ls->fs, &e);  /* close last expression */
      luaK_storevar(ls->fs, &lh->v, &e);
      return;  /* avoid default */
    }
  }
  init_exp(&e, VNONRELOC, ls->fs->freereg-1);  /* default assignment */
  luaK_storevar(ls->fs, &lh->v, &e);
}