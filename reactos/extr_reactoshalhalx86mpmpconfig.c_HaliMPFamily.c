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
typedef  int ULONG ;
typedef  char* PCHAR ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

PCHAR 
HaliMPFamily(ULONG Family,
	     ULONG Model)
{
   static CHAR str[64];
   static PCHAR CPUs[] =
   {
      "80486DX", "80486DX",
      "80486SX", "80486DX/2 or 80487",
      "80486SL", "Intel5X2(tm)",
      "Unknown", "Unknown",
      "80486DX/4"
   };
   if (Family == 0x6)
      return ("Pentium(tm) Pro");
   if (Family == 0x5)
      return ("Pentium(tm)");
   if (Family == 0x0F && Model == 0x0F)
      return("Special controller");
   if (Family == 0x0F && Model == 0x00)
      return("Pentium 4(tm)");
   if (Family == 0x04 && Model < 9)
      return CPUs[Model];
   sprintf(str, "Unknown CPU with family ID %ld and model ID %ld", Family, Model);
   return str;
}