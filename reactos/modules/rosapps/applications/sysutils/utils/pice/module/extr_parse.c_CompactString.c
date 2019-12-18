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
 int /*<<< orphan*/  PICE_strcpy (char*,char*) ; 
 size_t PICE_strlen (char*) ; 

void CompactString(LPSTR p)
{
ULONG i;

	for(i=1;i<PICE_strlen(p);i++)
	{
		if(p[i]==' ' && p[i-1]==' ')
		{
			PICE_strcpy(&p[i-1],&p[i]);
			i=1;
		}
	}
}