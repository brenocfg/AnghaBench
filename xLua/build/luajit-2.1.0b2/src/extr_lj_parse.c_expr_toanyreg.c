#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ info; } ;
struct TYPE_14__ {TYPE_2__ s; } ;
struct TYPE_17__ {scalar_t__ k; TYPE_1__ u; } ;
struct TYPE_16__ {scalar_t__ nactvar; } ;
typedef  TYPE_3__ FuncState ;
typedef  TYPE_4__ ExpDesc ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 scalar_t__ VNONRELOC ; 
 int /*<<< orphan*/  expr_discharge (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  expr_hasjump (TYPE_4__*) ; 
 int /*<<< orphan*/  expr_tonextreg (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  expr_toreg (TYPE_3__*,TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static BCReg expr_toanyreg(FuncState *fs, ExpDesc *e)
{
  expr_discharge(fs, e);
  if (e->k == VNONRELOC) {
    if (!expr_hasjump(e)) return e->u.s.info;  /* Already in a register. */
    if (e->u.s.info >= fs->nactvar) {
      expr_toreg(fs, e, e->u.s.info);  /* Discharge to temp. register. */
      return e->u.s.info;
    }
  }
  expr_tonextreg(fs, e);  /* Discharge to next register. */
  return e->u.s.info;
}