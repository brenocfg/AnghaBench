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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 

__attribute__((used)) static
BOOL
KdbGetHexNumber(char *pszNum, ULONG_PTR *pulValue)
{
    char *endptr;

    /* Skip optional '0x' prefix */
    if ((pszNum[0] == '0') && ((pszNum[1] == 'x') || (pszNum[1] == 'X')))
        pszNum += 2;

    /* Make a number from the string (hex) */
    *pulValue = strtoul(pszNum, &endptr, 16);

    return (*endptr == '\0');
}