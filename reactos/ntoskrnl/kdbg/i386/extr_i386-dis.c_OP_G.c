#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int DFLAG ; 
 int /*<<< orphan*/  INTERNAL_DISASSEMBLER_ERROR ; 
 int PREFIX_DATA ; 
 int REX_EXTX ; 
 int REX_MODE64 ; 
 int /*<<< orphan*/  USED_REX (int) ; 
#define  b_mode 132 
#define  d_mode 131 
 int /*<<< orphan*/ * names16 ; 
 int /*<<< orphan*/ * names32 ; 
 int /*<<< orphan*/ * names64 ; 
 int /*<<< orphan*/ * names8 ; 
 int /*<<< orphan*/ * names8rex ; 
 int /*<<< orphan*/  oappend (int /*<<< orphan*/ ) ; 
 int prefixes ; 
#define  q_mode 130 
 int /*<<< orphan*/  reg ; 
 int rex ; 
 int used_prefixes ; 
#define  v_mode 129 
#define  w_mode 128 

__attribute__((used)) static void
OP_G (int bytemode, int sizeflag)
{
  int add = 0;
  USED_REX (REX_EXTX);
  if (rex & REX_EXTX)
    add += 8;
  switch (bytemode)
    {
    case b_mode:
      USED_REX (0);
      if (rex)
	oappend (names8rex[reg + add]);
      else
	oappend (names8[reg + add]);
      break;
    case w_mode:
      oappend (names16[reg + add]);
      break;
    case d_mode:
      oappend (names32[reg + add]);
      break;
    case q_mode:
      oappend (names64[reg + add]);
      break;
    case v_mode:
      USED_REX (REX_MODE64);
      if (rex & REX_MODE64)
	oappend (names64[reg + add]);
      else if (sizeflag & DFLAG)
	oappend (names32[reg + add]);
      else
	oappend (names16[reg + add]);
      used_prefixes |= (prefixes & PREFIX_DATA);
      break;
    default:
      oappend (INTERNAL_DISASSEMBLER_ERROR);
      break;
    }
}