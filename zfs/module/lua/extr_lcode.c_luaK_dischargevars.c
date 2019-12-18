#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int const vt; void* idx; void* t; } ;
struct TYPE_7__ {TYPE_1__ ind; void* info; } ;
struct TYPE_8__ {int k; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
typedef  int /*<<< orphan*/  OpCode ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_GETTABLE ; 
 int /*<<< orphan*/  OP_GETTABUP ; 
 int /*<<< orphan*/  OP_GETUPVAL ; 
#define  VCALL 132 
#define  VINDEXED 131 
#define  VLOCAL 130 
 int VNONRELOC ; 
 void* VRELOCABLE ; 
#define  VUPVAL 129 
#define  VVARARG 128 
 int /*<<< orphan*/  freereg (int /*<<< orphan*/ *,void*) ; 
 void* luaK_codeABC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  luaK_setoneret (int /*<<< orphan*/ *,TYPE_3__*) ; 

void luaK_dischargevars (FuncState *fs, expdesc *e) {
  switch (e->k) {
    case VLOCAL: {
      e->k = VNONRELOC;
      break;
    }
    case VUPVAL: {
      e->u.info = luaK_codeABC(fs, OP_GETUPVAL, 0, e->u.info, 0);
      e->k = VRELOCABLE;
      break;
    }
    case VINDEXED: {
      OpCode op = OP_GETTABUP;  /* assume 't' is in an upvalue */
      freereg(fs, e->u.ind.idx);
      if (e->u.ind.vt == VLOCAL) {  /* 't' is in a register? */
        freereg(fs, e->u.ind.t);
        op = OP_GETTABLE;
      }
      e->u.info = luaK_codeABC(fs, op, 0, e->u.ind.t, e->u.ind.idx);
      e->k = VRELOCABLE;
      break;
    }
    case VVARARG:
    case VCALL: {
      luaK_setoneret(fs, e);
      break;
    }
    default: break;  /* there is one value available (somewhere) */
  }
}