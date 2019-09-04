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

/* Variables and functions */
 scalar_t__ IsAddressValid (scalar_t__) ; 
 scalar_t__ PICE_toupper (char) ; 

ULONG PICE_strncmpi(char* s1,char* s2,ULONG len)
{
ULONG result=1;

    while(len &&
		  IsAddressValid((ULONG)s1) && *s1 && // not end of string
          IsAddressValid((ULONG)s2) && *s2 && // not end of string
          PICE_toupper(*s1)==PICE_toupper(*s2) ) // char are the same except case
    {
        s1++;
        s2++;
		len--;
    }
	// strings same length
    if(len==0)
        result=0;

    return result;
}