#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int flags; } ;
typedef  int Reg ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int JIT_F_LEA_AGU ; 
 int REX_GC64 ; 
 int /*<<< orphan*/  XG_ARITHi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_LEA ; 
 int /*<<< orphan*/  XOg_ADD ; 
 int /*<<< orphan*/  emit_gri (TYPE_1__*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_1__*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 

__attribute__((used)) static void emit_addptr(ASMState *as, Reg r, int32_t ofs)
{
  if (ofs) {
    if ((as->flags & JIT_F_LEA_AGU))
      emit_rmro(as, XO_LEA, r|REX_GC64, r, ofs);
    else
      emit_gri(as, XG_ARITHi(XOg_ADD), r|REX_GC64, ofs);
  }
}