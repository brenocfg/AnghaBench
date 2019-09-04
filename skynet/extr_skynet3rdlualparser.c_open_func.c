#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* f; int /*<<< orphan*/ * bl; int /*<<< orphan*/  firstlocal; scalar_t__ nactvar; scalar_t__ nlocvars; scalar_t__ nups; scalar_t__ np; scalar_t__ nk; scalar_t__ freereg; int /*<<< orphan*/  jpc; scalar_t__ lasttarget; scalar_t__ pc; TYPE_5__* ls; struct TYPE_15__* prev; } ;
struct TYPE_14__ {int /*<<< orphan*/  source; TYPE_2__* dyd; TYPE_6__* fs; } ;
struct TYPE_13__ {int maxstacksize; int /*<<< orphan*/  source; } ;
struct TYPE_12__ {TYPE_4__* sp; } ;
struct TYPE_10__ {int /*<<< orphan*/  n; } ;
struct TYPE_11__ {TYPE_1__ actvar; } ;
typedef  TYPE_4__ SharedProto ;
typedef  TYPE_5__ LexState ;
typedef  TYPE_6__ FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  NO_JUMP ; 
 int /*<<< orphan*/  enterblock (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void open_func (LexState *ls, FuncState *fs, BlockCnt *bl) {
  SharedProto *f;
  fs->prev = ls->fs;  /* linked list of funcstates */
  fs->ls = ls;
  ls->fs = fs;
  fs->pc = 0;
  fs->lasttarget = 0;
  fs->jpc = NO_JUMP;
  fs->freereg = 0;
  fs->nk = 0;
  fs->np = 0;
  fs->nups = 0;
  fs->nlocvars = 0;
  fs->nactvar = 0;
  fs->firstlocal = ls->dyd->actvar.n;
  fs->bl = NULL;
  f = fs->f->sp;
  f->source = ls->source;
  f->maxstacksize = 2;  /* registers 0/1 are always valid */
  enterblock(fs, bl, 0);
}