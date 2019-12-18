#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_12__ {int /*<<< orphan*/  tmptv2; } ;
typedef  int /*<<< orphan*/  MMS ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int /*<<< orphan*/  CDArith ;

/* Variables and functions */
 TYPE_9__* G (TYPE_1__*) ; 
 scalar_t__ carith_checkarg (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ carith_int64 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ carith_ptr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyTV (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ctype_cts (TYPE_1__*) ; 
 int lj_carith_meta (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int lj_carith_op(lua_State *L, MMS mm)
{
  CTState *cts = ctype_cts(L);
  CDArith ca;
  if (carith_checkarg(L, cts, &ca)) {
    if (carith_int64(L, cts, &ca, mm) || carith_ptr(L, cts, &ca, mm)) {
      copyTV(L, &G(L)->tmptv2, L->top-1);  /* Remember for trace recorder. */
      return 1;
    }
  }
  return lj_carith_meta(L, cts, &ca, mm);
}