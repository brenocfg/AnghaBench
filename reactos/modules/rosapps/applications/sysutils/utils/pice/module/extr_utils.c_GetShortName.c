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
typedef  size_t ULONG ;
typedef  char* LPSTR ;

/* Variables and functions */
 size_t PICE_strlen (char*) ; 

LPSTR GetShortName(LPSTR p)
{
ULONG i;

	// scan backwards till backslash or start
	for(i=PICE_strlen(p);p[i]!='\\' && &p[i]!=p;i--);
	// it's not start, inc. counter
	if(&p[i]!=p)i++;

	// return section of string containing mod name
	return &p[i];
}