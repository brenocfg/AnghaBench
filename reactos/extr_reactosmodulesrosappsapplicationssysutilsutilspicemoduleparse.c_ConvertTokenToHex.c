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
typedef  scalar_t__ USHORT ;
typedef  int ULONG ;
typedef  scalar_t__ UCHAR ;
typedef  int* PULONG ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GetLinearAddress (scalar_t__,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int gCurrentOffset ; 
 scalar_t__ gCurrentSelector ; 

BOOLEAN ConvertTokenToHex(LPSTR p,PULONG pValue)
{
ULONG result=0,i;

	gCurrentSelector=0;
	gCurrentOffset=0;
	for(i=0;i<8 && p[i]!=0 && p[i]!=' ' && p[i]!=':';i++)
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
	p+=(i+1);
	if(p[i]==':')
	{
		ULONG ulSelector=result;
		if(ulSelector>0xFFFF)
			return FALSE;
		for(i=0;i<8 && p[i]!=0 && p[i]!=' ' && p[i]!=':';i++)
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
		gCurrentSelector=(USHORT)ulSelector;
		gCurrentOffset=result;
		result = GetLinearAddress((USHORT)ulSelector,result);
	}
	*pValue=result;
	return TRUE;
}