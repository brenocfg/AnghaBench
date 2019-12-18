#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ info; } ;
struct TYPE_19__ {TYPE_1__ s; } ;
struct TYPE_21__ {int /*<<< orphan*/  k; TYPE_2__ u; } ;
struct TYPE_20__ {scalar_t__ freereg; } ;
typedef  TYPE_3__ FuncState ;
typedef  TYPE_4__ ExpDesc ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 scalar_t__ BCMAX_C ; 
 int /*<<< orphan*/  BC_KSTR ; 
 int /*<<< orphan*/  BC_MOV ; 
 int /*<<< orphan*/  BC_TGETS ; 
 int /*<<< orphan*/  BC_TGETV ; 
 scalar_t__ LJ_FR2 ; 
 int /*<<< orphan*/  VNONRELOC ; 
 int /*<<< orphan*/  bcemit_ABC (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bcemit_AD (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bcreg_reserve (TYPE_3__*,scalar_t__) ; 
 scalar_t__ const_str (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  expr_free (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  expr_isstrk (TYPE_4__*) ; 
 scalar_t__ expr_toanyreg (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcemit_method(FuncState *fs, ExpDesc *e, ExpDesc *key)
{
  BCReg idx, func, obj = expr_toanyreg(fs, e);
  expr_free(fs, e);
  func = fs->freereg;
  bcemit_AD(fs, BC_MOV, func+1+LJ_FR2, obj);  /* Copy object to 1st argument. */
  lua_assert(expr_isstrk(key));
  idx = const_str(fs, key);
  if (idx <= BCMAX_C) {
    bcreg_reserve(fs, 2+LJ_FR2);
    bcemit_ABC(fs, BC_TGETS, func, obj, idx);
  } else {
    bcreg_reserve(fs, 3+LJ_FR2);
    bcemit_AD(fs, BC_KSTR, func+2+LJ_FR2, idx);
    bcemit_ABC(fs, BC_TGETV, func, obj, func+2+LJ_FR2);
    fs->freereg--;
  }
  e->u.s.info = func;
  e->k = VNONRELOC;
}