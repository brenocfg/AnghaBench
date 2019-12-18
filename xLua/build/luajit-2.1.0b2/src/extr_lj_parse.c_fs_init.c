#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_11__ {int framesize; int /*<<< orphan*/  kt; scalar_t__ flags; int /*<<< orphan*/ * bl; scalar_t__ nuv; scalar_t__ nactvar; scalar_t__ nkn; scalar_t__ nkgc; scalar_t__ freereg; int /*<<< orphan*/  jpc; scalar_t__ lasttarget; scalar_t__ pc; TYPE_1__* L; int /*<<< orphan*/  vbase; TYPE_2__* ls; struct TYPE_11__* prev; } ;
struct TYPE_10__ {int /*<<< orphan*/  vtop; TYPE_3__* fs; TYPE_1__* L; } ;
typedef  TYPE_2__ LexState ;
typedef  TYPE_3__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  NO_JMP ; 
 int /*<<< orphan*/  incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_tab_new (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settabV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_init(LexState *ls, FuncState *fs)
{
  lua_State *L = ls->L;
  fs->prev = ls->fs; ls->fs = fs;  /* Append to list. */
  fs->ls = ls;
  fs->vbase = ls->vtop;
  fs->L = L;
  fs->pc = 0;
  fs->lasttarget = 0;
  fs->jpc = NO_JMP;
  fs->freereg = 0;
  fs->nkgc = 0;
  fs->nkn = 0;
  fs->nactvar = 0;
  fs->nuv = 0;
  fs->bl = NULL;
  fs->flags = 0;
  fs->framesize = 1;  /* Minimum frame size. */
  fs->kt = lj_tab_new(L, 0, 0);
  /* Anchor table of constants in stack to avoid being collected. */
  settabV(L, L->top, fs->kt);
  incr_top(L);
}