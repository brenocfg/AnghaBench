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
 int /*<<< orphan*/  FETCH_DATA (int /*<<< orphan*/ ,int*) ; 
#define  FWAIT_OPCODE 128 
 scalar_t__ PREFIX_ADDR ; 
 scalar_t__ PREFIX_CS ; 
 scalar_t__ PREFIX_DATA ; 
 scalar_t__ PREFIX_DS ; 
 scalar_t__ PREFIX_ES ; 
 scalar_t__ PREFIX_FS ; 
 scalar_t__ PREFIX_FWAIT ; 
 scalar_t__ PREFIX_GS ; 
 scalar_t__ PREFIX_LOCK ; 
 scalar_t__ PREFIX_REPNZ ; 
 scalar_t__ PREFIX_REPZ ; 
 scalar_t__ PREFIX_SS ; 
 int* codep ; 
 int /*<<< orphan*/  mode_64bit ; 
 int /*<<< orphan*/  oappend (char*) ; 
 char* prefix_name (int,int /*<<< orphan*/ ) ; 
 scalar_t__ prefixes ; 
 int rex ; 
 scalar_t__ rex_used ; 
 int /*<<< orphan*/  the_info ; 
 scalar_t__ used_prefixes ; 

__attribute__((used)) static void
ckprefix ()
{
  int newrex;
  rex = 0;
  prefixes = 0;
  used_prefixes = 0;
  rex_used = 0;
  while (1)
    {
      FETCH_DATA (the_info, codep + 1);
      newrex = 0;
      switch (*codep)
	{
	/* REX prefixes family.  */
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
	case 0x4a:
	case 0x4b:
	case 0x4c:
	case 0x4d:
	case 0x4e:
	case 0x4f:
	    if (mode_64bit)
	      newrex = *codep;
	    else
	      return;
	  break;
	case 0xf3:
	  prefixes |= PREFIX_REPZ;
	  break;
	case 0xf2:
	  prefixes |= PREFIX_REPNZ;
	  break;
	case 0xf0:
	  prefixes |= PREFIX_LOCK;
	  break;
	case 0x2e:
	  prefixes |= PREFIX_CS;
	  break;
	case 0x36:
	  prefixes |= PREFIX_SS;
	  break;
	case 0x3e:
	  prefixes |= PREFIX_DS;
	  break;
	case 0x26:
	  prefixes |= PREFIX_ES;
	  break;
	case 0x64:
	  prefixes |= PREFIX_FS;
	  break;
	case 0x65:
	  prefixes |= PREFIX_GS;
	  break;
	case 0x66:
	  prefixes |= PREFIX_DATA;
	  break;
	case 0x67:
	  prefixes |= PREFIX_ADDR;
	  break;
	case FWAIT_OPCODE:
	  /* fwait is really an instruction.  If there are prefixes
	     before the fwait, they belong to the fwait, *not* to the
	     following instruction.  */
	  if (prefixes)
	    {
	      prefixes |= PREFIX_FWAIT;
	      codep++;
	      return;
	    }
	  prefixes = PREFIX_FWAIT;
	  break;
	default:
	  return;
	}
      /* Rex is ignored when followed by another prefix.  */
      if (rex)
	{
	  oappend (prefix_name (rex, 0));
	  oappend (" ");
	}
      rex = newrex;
      codep++;
    }
}