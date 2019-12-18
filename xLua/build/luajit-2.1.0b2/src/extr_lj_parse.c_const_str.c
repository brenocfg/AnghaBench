#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sval; } ;
struct TYPE_6__ {scalar_t__ k; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  TYPE_2__ ExpDesc ;
typedef  int /*<<< orphan*/  BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_TSTR ; 
 scalar_t__ VGLOBAL ; 
 int /*<<< orphan*/  const_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ expr_isstrk (TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BCReg const_str(FuncState *fs, ExpDesc *e)
{
  lua_assert(expr_isstrk(e) || e->k == VGLOBAL);
  return const_gc(fs, obj2gco(e->u.sval), LJ_TSTR);
}