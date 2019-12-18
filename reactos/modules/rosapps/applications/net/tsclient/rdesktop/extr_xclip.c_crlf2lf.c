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
typedef  char uint8 ;
typedef  int uint32 ;

/* Variables and functions */

__attribute__((used)) static void
crlf2lf(uint8 * data, uint32 * length)
{
	uint8 *dst, *src;
	src = dst = data;
	while (src < data + *length)
	{
		if (*src != '\x0d')
			*dst++ = *src;
		src++;
	}
	*length = dst - data;
}