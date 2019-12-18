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
 int /*<<< orphan*/  CompactString (char*) ; 
 size_t PICE_strlen (char*) ; 

char* PICE_strtok(char *szInputString)
{
static char* szCurrString;
char *szTempString;
ULONG currlength;
ULONG i;

	if(szInputString)
	{
		szCurrString=szInputString;
		CompactString(szCurrString);
	}

	currlength=PICE_strlen(szCurrString);
	if(!currlength)
	{
		szCurrString=0;
		return NULL;
	}
	for(i=0;i<currlength;i++)
	{
		if(szCurrString[i]==' ')
		{
			szCurrString[i]=0;
			break;
		}
	}
	szTempString=szCurrString;
	szCurrString=szCurrString+i+1;
	return szTempString;
}