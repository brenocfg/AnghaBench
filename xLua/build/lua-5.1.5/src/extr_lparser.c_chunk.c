#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  token; } ;
struct TYPE_13__ {TYPE_2__* fs; TYPE_3__ t; } ;
struct TYPE_11__ {scalar_t__ freereg; scalar_t__ nactvar; TYPE_1__* f; } ;
struct TYPE_10__ {scalar_t__ maxstacksize; } ;
typedef  TYPE_4__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  block_follow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enterlevel (TYPE_4__*) ; 
 int /*<<< orphan*/  leavelevel (TYPE_4__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int statement (TYPE_4__*) ; 
 int /*<<< orphan*/  testnext (TYPE_4__*,char) ; 

__attribute__((used)) static void chunk (LexState *ls) {
  /* chunk -> { stat [`;'] } */
  int islast = 0;
  enterlevel(ls);
  while (!islast && !block_follow(ls->t.token)) {
    islast = statement(ls);
    testnext(ls, ';');
    lua_assert(ls->fs->f->maxstacksize >= ls->fs->freereg &&
               ls->fs->freereg >= ls->fs->nactvar);
    ls->fs->freereg = ls->fs->nactvar;  /* free registers */
  }
  leavelevel(ls);
}