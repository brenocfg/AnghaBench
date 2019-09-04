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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static LONG DecodeBinaryToBinaryA(LPCSTR pszString, DWORD cchString,
 BYTE *pbBinary, DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags)
{
    LONG ret = ERROR_SUCCESS;

    if (*pcbBinary < cchString)
    {
        if (!pbBinary)
            *pcbBinary = cchString;
        else
        {
            ret = ERROR_INSUFFICIENT_BUFFER;
            *pcbBinary = cchString;
        }
    }
    else
    {
        if (cchString)
            memcpy(pbBinary, pszString, cchString);
        *pcbBinary = cchString;
    }
    return ret;
}