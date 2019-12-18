#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ k; } ;
typedef  TYPE_1__ expdesc ;
struct TYPE_12__ {struct TYPE_12__* prev; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 scalar_t__ VLOCAL ; 
 scalar_t__ VUPVAL ; 
 scalar_t__ VVOID ; 
 int /*<<< orphan*/  init_exp (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  markupval (TYPE_2__*,int) ; 
 int newupvalue (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int searchupvalue (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int searchvar (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void singlevaraux (FuncState *fs, TString *n, expdesc *var, int base) {
  if (fs == NULL)  /* no more levels? */
    init_exp(var, VVOID, 0);  /* default is global */
  else {
    int v = searchvar(fs, n);  /* look up locals at current level */
    if (v >= 0) {  /* found? */
      init_exp(var, VLOCAL, v);  /* variable is local */
      if (!base)
        markupval(fs, v);  /* local will be used as an upval */
    }
    else {  /* not found as local at current level; try upvalues */
      int idx = searchupvalue(fs, n);  /* try existing upvalues */
      if (idx < 0) {  /* not found? */
        singlevaraux(fs->prev, n, var, 0);  /* try upper levels */
        if (var->k == VVOID)  /* not found? */
          return;  /* it is a global */
        /* else was LOCAL or UPVAL */
        idx  = newupvalue(fs, n, var);  /* will be a new upvalue */
      }
      init_exp(var, VUPVAL, idx);  /* new or old upvalue */
    }
  }
}