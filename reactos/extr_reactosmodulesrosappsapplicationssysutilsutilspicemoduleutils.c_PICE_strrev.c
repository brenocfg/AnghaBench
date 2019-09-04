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

/* Variables and functions */
 size_t PICE_strlen (char*) ; 

char* PICE_strrev(char* s)
{
ULONG i,j,len=PICE_strlen(s)-1;
char c;

	for(i=0,j=len;i<j;i++,j--)
	{
		c=s[i]; s[i]=s[j]; s[j]=c;
	}

	return s;
}