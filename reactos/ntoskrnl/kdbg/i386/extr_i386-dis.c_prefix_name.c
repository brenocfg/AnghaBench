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
 int AFLAG ; 
 int DFLAG ; 
#define  FWAIT_OPCODE 128 
 int /*<<< orphan*/  mode_64bit ; 

__attribute__((used)) static const char *
prefix_name (int pref, int sizeflag)
{
  switch (pref)
    {
    /* REX prefixes family.  */
    case 0x40:
      return "rex";
    case 0x41:
      return "rexZ";
    case 0x42:
      return "rexY";
    case 0x43:
      return "rexYZ";
    case 0x44:
      return "rexX";
    case 0x45:
      return "rexXZ";
    case 0x46:
      return "rexXY";
    case 0x47:
      return "rexXYZ";
    case 0x48:
      return "rex64";
    case 0x49:
      return "rex64Z";
    case 0x4a:
      return "rex64Y";
    case 0x4b:
      return "rex64YZ";
    case 0x4c:
      return "rex64X";
    case 0x4d:
      return "rex64XZ";
    case 0x4e:
      return "rex64XY";
    case 0x4f:
      return "rex64XYZ";
    case 0xf3:
      return "repz";
    case 0xf2:
      return "repnz";
    case 0xf0:
      return "lock";
    case 0x2e:
      return "cs";
    case 0x36:
      return "ss";
    case 0x3e:
      return "ds";
    case 0x26:
      return "es";
    case 0x64:
      return "fs";
    case 0x65:
      return "gs";
    case 0x66:
      return (sizeflag & DFLAG) ? "data16" : "data32";
    case 0x67:
      if (mode_64bit)
	return (sizeflag & AFLAG) ? "addr32" : "addr64";
      else
	return ((sizeflag & AFLAG) && !mode_64bit) ? "addr16" : "addr32";
    case FWAIT_OPCODE:
      return "fwait";
    default:
      return NULL;
    }
}