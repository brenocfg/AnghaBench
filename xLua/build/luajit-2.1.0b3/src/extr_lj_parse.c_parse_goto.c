#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  slot; } ;
typedef  TYPE_2__ VarInfo ;
struct TYPE_15__ {TYPE_1__* bl; } ;
struct TYPE_14__ {TYPE_4__* fs; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  BC_LOOP ; 
 int /*<<< orphan*/  FSCOPE_GOLA ; 
 int /*<<< orphan*/  VSTACK_GOTO ; 
 int /*<<< orphan*/  bcemit_AJ (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcemit_jmp (TYPE_4__*) ; 
 TYPE_2__* gola_findlabel (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gola_new (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lex_str (TYPE_3__*) ; 

__attribute__((used)) static void parse_goto(LexState *ls)
{
  FuncState *fs = ls->fs;
  GCstr *name = lex_str(ls);
  VarInfo *vl = gola_findlabel(ls, name);
  if (vl)  /* Treat backwards goto within same scope like a loop. */
    bcemit_AJ(fs, BC_LOOP, vl->slot, -1);  /* No BC range check. */
  fs->bl->flags |= FSCOPE_GOLA;
  gola_new(ls, name, VSTACK_GOTO, bcemit_jmp(fs));
}