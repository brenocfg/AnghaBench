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
typedef  char* LPSTR ;

/* Variables and functions */

LPSTR TruncateString(LPSTR p,char c)
{
	static char temp[1024];
	LPSTR pTemp;

	pTemp = temp;

	while(*p!=0 && *p!=c)
		*pTemp++ = *p++;

	*pTemp = 0;

	return temp;
}