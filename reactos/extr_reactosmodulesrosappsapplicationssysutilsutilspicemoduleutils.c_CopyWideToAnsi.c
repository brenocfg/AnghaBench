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
typedef  int* PWSTR ;
typedef  char* LPSTR ;

/* Variables and functions */

void CopyWideToAnsi(LPSTR pAnsi,PWSTR pWide)
{
ULONG j;

	for(j=0;pWide[j]!=0;j++)
	{
        if((char)(pWide[j]>>8)==0)
		    pAnsi[j]=(char)(pWide[j]);
        else
            pAnsi[j]=0x20;
	}
	pAnsi[j]=0;

}