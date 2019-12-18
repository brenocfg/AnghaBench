#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ nactvar; int flags; struct TYPE_14__* prev; } ;
struct TYPE_13__ {scalar_t__ freereg; scalar_t__ nactvar; int /*<<< orphan*/  pc; TYPE_3__* bl; TYPE_1__* ls; } ;
struct TYPE_12__ {int /*<<< orphan*/  vtop; } ;
typedef  int /*<<< orphan*/  MSize ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ FuncState ;
typedef  TYPE_3__ FuncScope ;

/* Variables and functions */
 int /*<<< orphan*/  BC_UCLO ; 
 int FSCOPE_BREAK ; 
 int FSCOPE_GOLA ; 
 int FSCOPE_LOOP ; 
 int FSCOPE_NOCLOSE ; 
 int FSCOPE_UPVAL ; 
 int /*<<< orphan*/  NAME_BREAK ; 
 int /*<<< orphan*/  VSTACK_LABEL ; 
 int /*<<< orphan*/  bcemit_AJ (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gola_fixup (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gola_new (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gola_resolve (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  var_remove (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void fscope_end(FuncState *fs)
{
  FuncScope *bl = fs->bl;
  LexState *ls = fs->ls;
  fs->bl = bl->prev;
  var_remove(ls, bl->nactvar);
  fs->freereg = fs->nactvar;
  lua_assert(bl->nactvar == fs->nactvar);
  if ((bl->flags & (FSCOPE_UPVAL|FSCOPE_NOCLOSE)) == FSCOPE_UPVAL)
    bcemit_AJ(fs, BC_UCLO, bl->nactvar, 0);
  if ((bl->flags & FSCOPE_BREAK)) {
    if ((bl->flags & FSCOPE_LOOP)) {
      MSize idx = gola_new(ls, NAME_BREAK, VSTACK_LABEL, fs->pc);
      ls->vtop = idx;  /* Drop break label immediately. */
      gola_resolve(ls, bl, idx);
    } else {  /* Need the fixup step to propagate the breaks. */
      gola_fixup(ls, bl);
      return;
    }
  }
  if ((bl->flags & FSCOPE_GOLA)) {
    gola_fixup(ls, bl);
  }
}