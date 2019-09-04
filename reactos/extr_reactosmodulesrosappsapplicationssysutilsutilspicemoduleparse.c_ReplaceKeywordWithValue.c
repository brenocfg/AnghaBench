#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  size_t ULONG ;
struct TYPE_3__ {int ulSize; int /*<<< orphan*/  pValue; int /*<<< orphan*/ * KeyWord; } ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  size_t* PULONG ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  TYPE_1__ KEYWORDS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PICE_strcmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ReplaceKeywordWithValue(LPSTR p,PULONG pValue,KEYWORDS* pKeyWords)
{
    ULONG i;

	for(i=0;pKeyWords[i].KeyWord!=NULL;i++)
	{
		if(PICE_strcmpi(p,pKeyWords[i].KeyWord)==0)
		{
			switch(pKeyWords[i].ulSize)
			{
				case sizeof(USHORT):
					*pValue=(ULONG)*(PUSHORT)(pKeyWords[i].pValue);
					break;
				case sizeof(ULONG):
					*pValue=*(PULONG)(pKeyWords[i].pValue);
					break;
			}
			return TRUE;
		}
	}
	return FALSE;
}