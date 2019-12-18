#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_2__ {int /*<<< orphan*/  tmpbuf; } ;
typedef  int /*<<< orphan*/  TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IRBUFHDR_RESET ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_P32 ; 
 int /*<<< orphan*/  IR_BUFHDR ; 
 TYPE_1__* J2G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TRef recff_bufhdr(jit_State *J)
{
  return emitir(IRT(IR_BUFHDR, IRT_P32),
		lj_ir_kptr(J, &J2G(J)->tmpbuf), IRBUFHDR_RESET);
}