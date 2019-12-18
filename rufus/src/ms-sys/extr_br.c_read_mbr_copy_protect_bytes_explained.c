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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char const* _ (char*) ; 
 int read_mbr_copy_protect_bytes (int /*<<< orphan*/ *) ; 

const char *read_mbr_copy_protect_bytes_explained(FILE *fp)
{
   uint16_t t = read_mbr_copy_protect_bytes(fp);
   switch(t)
   {
      case 0:
	 return _("not copy protected");
      case 0x5a5a:
	 return _("copy protected");
      default:
	 return _("unknown value");
   }
}