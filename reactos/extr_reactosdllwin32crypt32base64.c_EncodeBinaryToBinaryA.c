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
typedef  scalar_t__ LPSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static BOOL EncodeBinaryToBinaryA(const BYTE *pbBinary,
 DWORD cbBinary, DWORD dwFlags, LPSTR pszString, DWORD *pcchString)
{
    BOOL ret = TRUE;

    if (pszString)
    {
        if (*pcchString < cbBinary)
        {
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            ret = FALSE;
        }
        else if (cbBinary)
            memcpy(pszString, pbBinary, cbBinary);
    }
    else
        *pcchString = cbBinary;

    return ret;
}