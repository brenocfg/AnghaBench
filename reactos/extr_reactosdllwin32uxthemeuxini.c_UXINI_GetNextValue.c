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
 int /*<<< orphan*/  UXINI_UnGetToLine (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ UXINI_isspace (char) ; 

LPCWSTR UXINI_GetNextValue(PUXINI_FILE uf, DWORD *dwNameLen, LPCWSTR *lpValue, DWORD *dwValueLen)
{
    LPCWSTR lpLine;
    LPCWSTR lpLineEnd;
    LPCWSTR name = NULL;
    LPCWSTR value = NULL;
    DWORD vallen = 0;
    DWORD namelen = 0;
    DWORD dwLen;
    lpLine = UXINI_GetNextLine(uf, &dwLen);
    if(!lpLine)
        return NULL;
    if(lpLine[0] == '[') {
        UXINI_UnGetToLine(uf, lpLine);
        return NULL;
    }
    lpLineEnd = lpLine + dwLen;

    name = lpLine;
    while(namelen < dwLen && *lpLine != '=') {
        lpLine++;
        namelen++;
    }
    if(*lpLine != '=') return NULL;
    lpLine++;

    /* Remove whitespace from end of name */
    while(UXINI_isspace(name[namelen-1])) namelen--;
    /* Remove whitespace from beginning of value */
    while(UXINI_isspace(*lpLine) && lpLine < lpLineEnd) lpLine++;
    value = lpLine;
    vallen = dwLen-(value-name);

    *dwNameLen = namelen;
    *dwValueLen = vallen;
    *lpValue = value;

    return name;
}