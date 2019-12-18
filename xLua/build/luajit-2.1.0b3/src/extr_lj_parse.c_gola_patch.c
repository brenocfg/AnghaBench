#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t startpc; int /*<<< orphan*/  slot; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ VarInfo ;
struct TYPE_12__ {TYPE_1__* bcbase; } ;
struct TYPE_11__ {TYPE_4__* fs; } ;
struct TYPE_9__ {int /*<<< orphan*/  ins; } ;
typedef  TYPE_3__ LexState ;
typedef  TYPE_4__ FuncState ;
typedef  size_t BCPos ;

/* Variables and functions */
 int /*<<< orphan*/  jmp_patch (TYPE_4__*,size_t,size_t) ; 
 int /*<<< orphan*/  setbc_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcrefnull (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gola_patch(LexState *ls, VarInfo *vg, VarInfo *vl)
{
  FuncState *fs = ls->fs;
  BCPos pc = vg->startpc;
  setgcrefnull(vg->name);  /* Invalidate pending goto. */
  setbc_a(&fs->bcbase[pc].ins, vl->slot);
  jmp_patch(fs, pc, vl->startpc);
}