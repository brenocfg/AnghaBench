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
 int /*<<< orphan*/  BadOp () ; 
 int /*<<< orphan*/  OP_E (int,int) ; 
 int mod ; 
 int obuf ; 
 int reg ; 
 scalar_t__ rm ; 
 int /*<<< orphan*/  strcpy (int,char*) ; 
 int strlen (int) ; 

__attribute__((used)) static void
OP_0fae (int bytemode, int sizeflag)
{
  if (mod == 3)
    {
      if (reg == 7)
	strcpy (obuf + strlen (obuf) - sizeof ("clflush") + 1, "sfence");

      if (reg < 5 || rm != 0)
	{
	  BadOp ();	/* bad sfence, mfence, or lfence */
	  return;
	}
    }
  else if (reg != 7)
    {
      BadOp ();		/* bad clflush */
      return;
    }

  OP_E (bytemode, sizeflag);
}