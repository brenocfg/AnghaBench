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

__attribute__((used)) static int check_bom(const unsigned char** source, size_t *len)
{
	int this_bom    = 0;
	int further_bom = 0;

	if(*len < 2) return 0;

	if((*source)[0] == 0xff && (*source)[1] == 0xfe)
	this_bom = -1;

	if((*source)[0] == 0xfe && (*source)[1] == 0xff)
	this_bom = 1;

	/* Skip the detected BOM. */
	if(this_bom != 0)
	{
		*source += 2;
		*len    -= 2;
		/* Check for following BOMs. The last one wins! */
		further_bom = check_bom(source, len);
		if(further_bom == 0) return this_bom; /* End of the recursion. */
		else                 return further_bom;
	}
	else return 0;
}