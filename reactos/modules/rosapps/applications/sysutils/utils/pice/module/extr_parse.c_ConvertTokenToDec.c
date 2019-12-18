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
typedef  int* PULONG ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ConvertTokenToDec(LPSTR p,PULONG pValue)
{
    ULONG result=0;
    char c;

	while((c = *p))
	{
		if(c >= '0' && c <= '9')
		{
			result *= 10;
			result += (ULONG)(c - '0');
		}
		else
			return FALSE;

        p++;
	}
    *pValue = result;
    return TRUE;
}