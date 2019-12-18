#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int lo; int hi; } ;
struct TYPE_12__ {TYPE_1__ u32; } ;
struct TYPE_11__ {int hash; } ;
struct TYPE_10__ {int /*<<< orphan*/  t; } ;
typedef  TYPE_2__ IRIns ;

/* Variables and functions */
 int HASH_BIAS ; 
 int IRT_FALSE ; 
 int hashrot (int,int) ; 
 int /*<<< orphan*/  ir_kgc (TYPE_2__*) ; 
 TYPE_5__* ir_knum (TYPE_2__*) ; 
 TYPE_3__* ir_kstr (TYPE_2__*) ; 
 int irt_isgcv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isnil (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ispri (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isstr (int /*<<< orphan*/ ) ; 
 int irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int u32ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t ir_khash(IRIns *ir)
{
  uint32_t lo, hi;
  if (irt_isstr(ir->t)) {
    return ir_kstr(ir)->hash;
  } else if (irt_isnum(ir->t)) {
    lo = ir_knum(ir)->u32.lo;
    hi = ir_knum(ir)->u32.hi << 1;
  } else if (irt_ispri(ir->t)) {
    lua_assert(!irt_isnil(ir->t));
    return irt_type(ir->t)-IRT_FALSE;
  } else {
    lua_assert(irt_isgcv(ir->t));
    lo = u32ptr(ir_kgc(ir));
    hi = lo + HASH_BIAS;
  }
  return hashrot(lo, hi);
}