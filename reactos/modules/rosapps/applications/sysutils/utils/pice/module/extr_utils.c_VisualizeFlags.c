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
typedef  char UCHAR ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  FlagNames ;

/* Variables and functions */
 int /*<<< orphan*/  PICE_strrev (char*) ; 
 char PICE_toupper (char) ; 

LPSTR VisualizeFlags(ULONG EFlags)
{
    static UCHAR FlagNames[]={'c',0,'p',0,'a',0,'z','s','t','i','d','o'};
    ULONG i,j;
    static char temp[32];

	for(j=0,i=0;i<sizeof(FlagNames);i++)
	{
		if(FlagNames[i]!=0)
		{
			if(EFlags&1)
				temp[j++] = PICE_toupper(FlagNames[i]);
			else
				temp[j++] = FlagNames[i];
			temp[j++]=' ';
		}
		EFlags>>=1;
	}
	temp[j]=0;
	PICE_strrev(temp);
	return temp;
}