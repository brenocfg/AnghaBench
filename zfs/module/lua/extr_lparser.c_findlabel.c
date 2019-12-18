#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_6__* bl; } ;
struct TYPE_16__ {int firstlabel; scalar_t__ upval; } ;
struct TYPE_12__ {int n; TYPE_4__* arr; } ;
struct TYPE_11__ {TYPE_4__* arr; } ;
struct TYPE_15__ {TYPE_2__ label; TYPE_1__ gt; } ;
struct TYPE_14__ {scalar_t__ nactvar; int /*<<< orphan*/  pc; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {TYPE_7__* fs; TYPE_5__* dyd; } ;
typedef  TYPE_3__ LexState ;
typedef  TYPE_4__ Labeldesc ;
typedef  TYPE_5__ Dyndata ;
typedef  TYPE_6__ BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  closegoto (TYPE_3__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  luaK_patchclose (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ luaS_eqstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int findlabel (LexState *ls, int g) {
  int i;
  BlockCnt *bl = ls->fs->bl;
  Dyndata *dyd = ls->dyd;
  Labeldesc *gt = &dyd->gt.arr[g];
  /* check labels in current block for a match */
  for (i = bl->firstlabel; i < dyd->label.n; i++) {
    Labeldesc *lb = &dyd->label.arr[i];
    if (luaS_eqstr(lb->name, gt->name)) {  /* correct label? */
      if (gt->nactvar > lb->nactvar &&
          (bl->upval || dyd->label.n > bl->firstlabel))
        luaK_patchclose(ls->fs, gt->pc, lb->nactvar);
      closegoto(ls, g, lb);  /* close it */
      return 1;
    }
  }
  return 0;  /* label not found; cannot close goto */
}