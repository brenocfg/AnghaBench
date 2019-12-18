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
 int /*<<< orphan*/  MODRM_CHECK ; 
 int /*<<< orphan*/  OP_E (int,int) ; 
 int REX_EXTZ ; 
 int /*<<< orphan*/  USED_REX (int) ; 
 int /*<<< orphan*/  codep ; 
 scalar_t__ intel_syntax ; 
 int mod ; 
 int /*<<< orphan*/  oappend (scalar_t__) ; 
 int rex ; 
 int rm ; 
 scalar_t__ scratchbuf ; 
 int /*<<< orphan*/  sprintf (scalar_t__,char*,int) ; 

__attribute__((used)) static void
OP_EX (int bytemode, int sizeflag)
{
  int add = 0;
  if (mod != 3)
    {
      OP_E (bytemode, sizeflag);
      return;
    }
  USED_REX (REX_EXTZ);
  if (rex & REX_EXTZ)
    add = 8;

  /* Skip mod/rm byte.  */
  MODRM_CHECK;
  codep++;
  sprintf (scratchbuf, "%%xmm%d", rm + add);
  oappend (scratchbuf + intel_syntax);
}