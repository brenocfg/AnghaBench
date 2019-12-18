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
typedef  scalar_t__ WCHAR ;
typedef  int INT ;

/* Variables and functions */
 int GetMultiSzLength (scalar_t__*) ; 
 int /*<<< orphan*/  ReplaceChars (scalar_t__*,int,int,int) ; 

__attribute__((used)) static void
SzFromMultiSz(WCHAR *pszz)
{
    INT Length = GetMultiSzLength(pszz);
    //printf("Length: %d\n", Length);
    if (Length > 0)
    {
        ReplaceChars(pszz, Length - 1, L'\0', L'|');
        pszz[Length - 1] = 0;
    }
    else
    {
        pszz[0] = 0;
    }
    //printf("pszz: %S\n", pszz);
}