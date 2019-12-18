#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ nactvar; size_t firstgoto; struct TYPE_21__* previous; int /*<<< orphan*/  firstlabel; scalar_t__ isloop; scalar_t__ upval; } ;
struct TYPE_20__ {scalar_t__ nactvar; scalar_t__ freereg; TYPE_6__* bl; TYPE_4__* ls; } ;
struct TYPE_19__ {TYPE_3__* dyd; } ;
struct TYPE_17__ {size_t n; int /*<<< orphan*/ * arr; } ;
struct TYPE_16__ {int /*<<< orphan*/  n; } ;
struct TYPE_18__ {TYPE_2__ gt; TYPE_1__ label; } ;
typedef  TYPE_4__ LexState ;
typedef  TYPE_5__ FuncState ;
typedef  TYPE_6__ BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  breaklabel (TYPE_4__*) ; 
 int luaK_jump (TYPE_5__*) ; 
 int /*<<< orphan*/  luaK_patchclose (TYPE_5__*,int,scalar_t__) ; 
 int /*<<< orphan*/  luaK_patchtohere (TYPE_5__*,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  movegotosout (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  removevars (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  undefgoto (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void leaveblock (FuncState *fs) {
  BlockCnt *bl = fs->bl;
  LexState *ls = fs->ls;
  if (bl->previous && bl->upval) {
    /* create a 'jump to here' to close upvalues */
    int j = luaK_jump(fs);
    luaK_patchclose(fs, j, bl->nactvar);
    luaK_patchtohere(fs, j);
  }
  if (bl->isloop)
    breaklabel(ls);  /* close pending breaks */
  fs->bl = bl->previous;
  removevars(fs, bl->nactvar);
  lua_assert(bl->nactvar == fs->nactvar);
  fs->freereg = fs->nactvar;  /* free registers */
  ls->dyd->label.n = bl->firstlabel;  /* remove local labels */
  if (bl->previous)  /* inner block? */
    movegotosout(fs, bl);  /* update pending gotos to outer block */
  else if (bl->firstgoto < ls->dyd->gt.n)  /* pending gotos in outer block? */
    undefgoto(ls, &ls->dyd->gt.arr[bl->firstgoto]);  /* error */
}