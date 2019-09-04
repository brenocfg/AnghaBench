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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertTokenToHex (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 scalar_t__ PICE_strtok (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int* pExports ; 
 int /*<<< orphan*/  strcmp (int*,char const*) ; 
 int* strstr (int*,char const*) ; 

BOOLEAN ScanExports(const char *pFind,PULONG pValue)
{
	char temp[256];
	LPSTR pStr=NULL;
	LPSTR pExp = pExports;
	BOOLEAN bResult = FALSE;

	ENTER_FUNC();
	DPRINT((0,"ScanExports pValue: %x\n", pValue));
nomatch:
	if(pExports)
		pStr = strstr(pExp,pFind);

	if(pStr)
	{
		LPSTR p;
		ULONG state;
		LPSTR pOldStr = pStr;

		for(;(*pStr!=0x0a && *pStr!=0x0d) && (ULONG)pStr>=(ULONG)pExports;pStr--);
		pStr++;
		p = temp;
		for(;(*pStr!=0x0a && *pStr!=0x0d);)*p++=*pStr++;
		*p=0;
		p = (LPSTR) PICE_strtok(temp," ");
		state=0;
		while(p)
		{
			switch(state)
			{
				case 0:
					ConvertTokenToHex(p,pValue);
					break;
				case 1:
					break;
				case 2:
					if(strcmp(p,pFind)!=0)
					{
						DPRINT((0,"Not: %s\n", p));
						pExp = pOldStr+1;
						goto nomatch;
					}
					state = -1;
					bResult = TRUE;
		            DPRINT((0,"%s @ %x\n",pFind,*pValue));
					goto exit;
					break;
			}
			state++;
			p = (char*) PICE_strtok(NULL," ");
		}
	}
exit:
	DPRINT((0,"%s %x @ %x\n",pFind,pValue,*pValue));

	LEAVE_FUNC();

	return bResult;
}