#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  ASMFunction ;

/* Variables and functions */
 scalar_t__ LJ_FR2 ; 
 int /*<<< orphan*/  copyTV (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ curr_funcisL (TYPE_1__*) ; 
 int /*<<< orphan*/ * curr_topL (TYPE_1__*) ; 
 int /*<<< orphan*/  setcont (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TValue *mmcall(lua_State *L, ASMFunction cont, cTValue *mo,
		    cTValue *a, cTValue *b)
{
  /*
  **           |-- framesize -> top       top+1       top+2 top+3
  ** before:   [func slots ...]
  ** mm setup: [func slots ...] [cont|?]  [mo|tmtype] [a]   [b]
  ** in asm:   [func slots ...] [cont|PC] [mo|delta]  [a]   [b]
  **           ^-- func base                          ^-- mm base
  ** after mm: [func slots ...]           [result]
  **                ^-- copy to base[PC_RA] --/     for lj_cont_ra
  **                          istruecond + branch   for lj_cont_cond*
  **                                       ignore   for lj_cont_nop
  ** next PC:  [func slots ...]
  */
  TValue *top = L->top;
  if (curr_funcisL(L)) top = curr_topL(L);
  setcont(top++, cont);  /* Assembler VM stores PC in upper word or FR2. */
  if (LJ_FR2) setnilV(top++);
  copyTV(L, top++, mo);  /* Store metamethod and two arguments. */
  if (LJ_FR2) setnilV(top++);
  copyTV(L, top, a);
  copyTV(L, top+1, b);
  return top;  /* Return new base. */
}