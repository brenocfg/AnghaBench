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
typedef  char* LPSTR ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int) ; 
 int /*<<< orphan*/  IsAddressValid (int) ; 
 scalar_t__ PICE_isdigit (char) ; 

LONG ExtractNumber(LPSTR p)
{
    LONG lMinus = 1,lBase;
    ULONG lNumber = 0;

    DPRINT((0,"ExtractNumber(): %s\n",p));

    if(!IsAddressValid((ULONG)p) )
    {
        DPRINT((1,"ExtractNumber(): [1] invalid page %x hit!\n",p));
        return 0;
    }

    if(*p == '-')
    {
        lMinus = -1;
        p++;
    }

    if(!IsAddressValid((ULONG)p) )
    {
        DPRINT((1,"ExtractNumber(): [2] invalid page %x hit!\n",p));
        return 0;
    }

    if(*p != '0') // non-octal -> decimal number
        lBase = 10;
    else
        lBase = 8;

    if(!IsAddressValid((ULONG)p) )
    {
        DPRINT((1,"ExtractNumber(): [3] invalid page %x hit!\n",p));
        return 0;
    }

    while(PICE_isdigit(*p))
    {
        lNumber *= lBase;
        lNumber += *p-'0';
        p++;
        if(!IsAddressValid((ULONG)p) )
        {
            DPRINT((1,"ExtractNumber(): [4] invalid page %x hit!\n",p));
            return 0;
        }
    }

    return (lNumber*lMinus);
}