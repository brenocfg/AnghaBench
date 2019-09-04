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
typedef  int /*<<< orphan*/  aucRef ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ contains_data (int /*<<< orphan*/ *,int,unsigned char*,int) ; 

int is_lilo_br(FILE *fp)
{
   /* A "file" is probably a LILO boot record if it contains the magic
      chars LILO at position 0x6 or 0x2 for floppies */
   unsigned char aucRef[] = {'L','I','L','O'};

   return ( contains_data(fp, 0x6, aucRef, sizeof(aucRef)) ||
	    contains_data(fp, 0x2, aucRef, sizeof(aucRef)) );
}