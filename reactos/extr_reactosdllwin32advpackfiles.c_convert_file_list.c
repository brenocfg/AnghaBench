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
typedef  char* LPSTR ;
typedef  char* LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lstrcpynA (char*,char const*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static LPSTR convert_file_list(LPCSTR FileList, DWORD *dwNumFiles)
{
    DWORD dwLen;
    const char *first = FileList;
    const char *last = FileList + strlen(FileList) - 1;
    LPSTR szConvertedList, temp;
    
    /* any number of these chars before the list is OK */
    while (first < last && (*first == ' ' || *first == '\t' || *first == ':'))
        first++;

    /* any number of these chars after the list is OK */
    while (last > first && (*last == ' ' || *last == '\t' || *last == ':'))
        last--;

    if (first == last)
        return NULL;

    dwLen = last - first + 3; /* room for double-null termination */
    szConvertedList = HeapAlloc(GetProcessHeap(), 0, dwLen);
    lstrcpynA(szConvertedList, first, dwLen - 1);
    szConvertedList[dwLen - 1] = '\0';

    /* empty list */
    if (!szConvertedList[0])
    {
        HeapFree(GetProcessHeap(), 0, szConvertedList);
        return NULL;
    }
        
    *dwNumFiles = 1;

    /* convert the colons to double-null termination */
    temp = szConvertedList;
    while (*temp)
    {
        if (*temp == ':')
        {
            *temp = '\0';
            (*dwNumFiles)++;
        }

        temp++;
    }

    return szConvertedList;
}