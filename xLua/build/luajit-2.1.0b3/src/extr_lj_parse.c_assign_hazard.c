#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ info; } ;
struct TYPE_16__ {TYPE_1__ s; } ;
struct TYPE_23__ {TYPE_2__ u; } ;
struct TYPE_22__ {scalar_t__ freereg; } ;
struct TYPE_17__ {scalar_t__ info; scalar_t__ aux; } ;
struct TYPE_18__ {TYPE_3__ s; } ;
struct TYPE_19__ {scalar_t__ k; TYPE_4__ u; } ;
struct TYPE_21__ {TYPE_5__ v; struct TYPE_21__* prev; } ;
struct TYPE_20__ {TYPE_8__* fs; } ;
typedef  TYPE_6__ LexState ;
typedef  TYPE_7__ LHSVarList ;
typedef  TYPE_8__ FuncState ;
typedef  TYPE_9__ ExpDesc ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  BC_MOV ; 
 scalar_t__ VINDEXED ; 
 int /*<<< orphan*/  bcemit_AD (TYPE_8__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bcreg_reserve (TYPE_8__*,int) ; 

__attribute__((used)) static void assign_hazard(LexState *ls, LHSVarList *lh, const ExpDesc *v)
{
  FuncState *fs = ls->fs;
  BCReg reg = v->u.s.info;  /* Check against this variable. */
  BCReg tmp = fs->freereg;  /* Rename to this temp. register (if needed). */
  int hazard = 0;
  for (; lh; lh = lh->prev) {
    if (lh->v.k == VINDEXED) {
      if (lh->v.u.s.info == reg) {  /* t[i], t = 1, 2 */
	hazard = 1;
	lh->v.u.s.info = tmp;
      }
      if (lh->v.u.s.aux == reg) {  /* t[i], i = 1, 2 */
	hazard = 1;
	lh->v.u.s.aux = tmp;
      }
    }
  }
  if (hazard) {
    bcemit_AD(fs, BC_MOV, tmp, reg);  /* Rename conflicting variable. */
    bcreg_reserve(fs, 1);
  }
}