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
typedef  int /*<<< orphan*/  PULONG ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PICE_strncpy (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ReplaceKeywordWithValue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpecialKeyWords ; 
 size_t StrLenUpToWhiteChar (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ConvertTokenToSpecialKeyword(LPSTR p,PULONG pValue)
{
    char Name[256];
    ULONG count;

	count=StrLenUpToWhiteChar(p," ");
	PICE_strncpy(Name,p,count);
	Name[count]=0;
	if(ReplaceKeywordWithValue(Name,pValue,SpecialKeyWords))
	{
		return TRUE;
	}
	return FALSE;
}