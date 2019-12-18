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
typedef  int /*<<< orphan*/  disassemble_info ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int intel_syntax ; 
 int print_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
print_insn_i386 (bfd_vma pc, disassemble_info *info)
{
  intel_syntax = -1;

  return print_insn (pc, info);
}