#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * (* pfnAlloc ) (int) ;} ;
typedef  int DWORD ;
typedef  TYPE_1__ CRYPT_DECODE_PARA ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CRYPT_DECODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * stub1 (int) ; 

__attribute__((used)) static BOOL CRYPT_DecodeEnsureSpace(DWORD dwFlags,
 const CRYPT_DECODE_PARA *pDecodePara, void *pvStructInfo, DWORD *pcbStructInfo,
 DWORD bytesNeeded)
{
    BOOL ret = TRUE;

    if (dwFlags & CRYPT_DECODE_ALLOC_FLAG)
    {
        if (pDecodePara && pDecodePara->pfnAlloc)
            *(BYTE **)pvStructInfo = pDecodePara->pfnAlloc(bytesNeeded);
        else
            *(BYTE **)pvStructInfo = LocalAlloc(LPTR, bytesNeeded);
        if (!*(BYTE **)pvStructInfo)
            ret = FALSE;
        else
            *pcbStructInfo = bytesNeeded;
    }
    else if (*pcbStructInfo < bytesNeeded)
    {
        *pcbStructInfo = bytesNeeded;
        SetLastError(ERROR_MORE_DATA);
        ret = FALSE;
    }
    else
        *pcbStructInfo = bytesNeeded;
    return ret;
}