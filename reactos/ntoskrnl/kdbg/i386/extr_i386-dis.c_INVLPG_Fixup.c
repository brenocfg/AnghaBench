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
 int /*<<< orphan*/  OP_E (int,int) ; 
 int* codep ; 
 char* obuf ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
INVLPG_Fixup (int bytemode, int sizeflag)
{
  if (*codep == 0xf8)
    {
      char *p = obuf + strlen (obuf);

      /* Override "invlpg".  */
      strcpy (p - 6, "swapgs");
      codep++;
    }
  else
    OP_E (bytemode, sizeflag);
}