#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int ffid; } ;
struct TYPE_4__ {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  MMS ;

/* Variables and functions */
 scalar_t__ FF_ffi_meta___eq ; 
 scalar_t__ MM_eq ; 
 TYPE_2__* curr_func (int /*<<< orphan*/ *) ; 
 int lj_carith_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ffi_arith(lua_State *L)
{
  MMS mm = (MMS)(curr_func(L)->c.ffid - (int)FF_ffi_meta___eq + (int)MM_eq);
  return lj_carith_op(L, mm);
}