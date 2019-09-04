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
typedef  int /*<<< orphan*/  PUXINI_FILE ;
typedef  char* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 char* UXINI_GetNextLine (int /*<<< orphan*/ ,int*) ; 

LPCWSTR UXINI_GetNextSection(PUXINI_FILE uf, DWORD *dwLen)
{
    LPCWSTR lpLine;
    while((lpLine = UXINI_GetNextLine(uf, dwLen))) {
        /* Assuming a ']' ending to the section name */
        if(lpLine[0] == '[') {
            lpLine++;
            *dwLen -= 2;
            break;
        }
    }
    return lpLine;
}