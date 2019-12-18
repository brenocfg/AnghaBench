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

__attribute__((used)) static unsigned long bit_read_long(unsigned char *buf, int *offset)
{
	unsigned long val =  /* 32 bit value */
		(((unsigned long) buf[*offset])   << 24)
	|	(((unsigned long) buf[*offset+1]) << 16)
	|	(((unsigned long) buf[*offset+2]) << 8)
	|	 ((unsigned long) buf[*offset+3]);
	*offset += 4;
	return val;
}