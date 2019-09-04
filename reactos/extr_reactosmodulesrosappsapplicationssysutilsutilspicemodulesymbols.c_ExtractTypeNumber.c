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
typedef  scalar_t__ LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int ExtractNumber (scalar_t__) ; 
 scalar_t__ PICE_strchr (scalar_t__,char) ; 

ULONG ExtractTypeNumber(LPSTR p)
{
	LPSTR pTypeNumber;
	ULONG ulTypeNumber = 0;

    DPRINT((0,"ExtractTypeNumber(%s)\n",p));

	pTypeNumber = PICE_strchr(p,'(');

	if(pTypeNumber)
	{
		pTypeNumber++;
		ulTypeNumber = ExtractNumber(pTypeNumber);
		ulTypeNumber <<= 16;
		pTypeNumber = PICE_strchr(p,',');
        if(pTypeNumber)
        {
		    pTypeNumber++;
		    ulTypeNumber += ExtractNumber(pTypeNumber);
        }
        else
        {
            ulTypeNumber = 0;
        }
	}
	return ulTypeNumber;
}