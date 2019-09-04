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
typedef  scalar_t__ UCHAR ;
typedef  int* PULONG ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ReadHex(LPSTR p,PULONG pValue)
{
    ULONG result=0,i;

	for(i=0;i<8 && p[i]!=0 && p[i]!=' ';i++)
	{
		if(p[i]>='0' && p[i]<='9')
		{
			result<<=4;
			result|=(ULONG)(UCHAR)(p[i]-'0');
		}
		else if(p[i]>='A' && p[i]<='F')
		{
			result<<=4;
			result|=(ULONG)(UCHAR)(p[i]-'A'+10);
		}
		else if(p[i]>='a' && p[i]<='f')
		{
			result<<=4;
			result|=(ULONG)(UCHAR)(p[i]-'a'+10);
		}
		else
			return FALSE;
	}

    *pValue = result;
    return TRUE;
}