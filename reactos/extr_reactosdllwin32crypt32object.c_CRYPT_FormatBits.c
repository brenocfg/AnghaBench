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
struct BitToString {int bit; int /*<<< orphan*/  str; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int LPWSTR ;
typedef  unsigned int DWORD ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  commaSpace ; 
 int /*<<< orphan*/  strcpyW (int,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL CRYPT_FormatBits(BYTE bits, const struct BitToString *map,
 DWORD mapEntries, void *pbFormat, DWORD *pcbFormat, BOOL *first)
{
    DWORD bytesNeeded = sizeof(WCHAR);
    unsigned int i;
    BOOL ret = TRUE, localFirst = *first;

    for (i = 0; i < mapEntries; i++)
        if (bits & map[i].bit)
        {
            if (!localFirst)
                bytesNeeded += strlenW(commaSpace) * sizeof(WCHAR);
            localFirst = FALSE;
            bytesNeeded += strlenW(map[i].str) * sizeof(WCHAR);
        }
    if (!pbFormat)
    {
        *first = localFirst;
        *pcbFormat = bytesNeeded;
    }
    else if (*pcbFormat < bytesNeeded)
    {
        *first = localFirst;
        *pcbFormat = bytesNeeded;
        SetLastError(ERROR_MORE_DATA);
        ret = FALSE;
    }
    else
    {
        LPWSTR str = pbFormat;

        localFirst = *first;
        *pcbFormat = bytesNeeded;
        for (i = 0; i < mapEntries; i++)
            if (bits & map[i].bit)
            {
                if (!localFirst)
                {
                    strcpyW(str, commaSpace);
                    str += strlenW(commaSpace);
                }
                localFirst = FALSE;
                strcpyW(str, map[i].str);
                str += strlenW(map[i].str);
            }
        *first = localFirst;
    }
    return ret;
}