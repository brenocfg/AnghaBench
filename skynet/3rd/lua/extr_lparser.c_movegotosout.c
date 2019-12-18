#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* dyd; } ;
struct TYPE_14__ {int firstgoto; int /*<<< orphan*/  nactvar; scalar_t__ upval; } ;
struct TYPE_13__ {TYPE_9__* ls; } ;
struct TYPE_12__ {int /*<<< orphan*/  nactvar; int /*<<< orphan*/  pc; } ;
struct TYPE_11__ {int n; TYPE_3__* arr; } ;
struct TYPE_10__ {TYPE_2__ gt; } ;
typedef  TYPE_2__ Labellist ;
typedef  TYPE_3__ Labeldesc ;
typedef  TYPE_4__ FuncState ;
typedef  TYPE_5__ BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  findlabel (TYPE_9__*,int) ; 
 int /*<<< orphan*/  luaK_patchclose (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void movegotosout (FuncState *fs, BlockCnt *bl) {
  int i = bl->firstgoto;
  Labellist *gl = &fs->ls->dyd->gt;
  /* correct pending gotos to current block and try to close it
     with visible labels */
  while (i < gl->n) {
    Labeldesc *gt = &gl->arr[i];
    if (gt->nactvar > bl->nactvar) {
      if (bl->upval)
        luaK_patchclose(fs, gt->pc, bl->nactvar);
      gt->nactvar = bl->nactvar;
    }
    if (!findlabel(fs->ls, i))
      i++;  /* move to next one */
  }
}