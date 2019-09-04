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
struct PATH_LEN_CONSTRAINT {int /*<<< orphan*/  dwPathLenConstraint; void* fPathLenConstraint; } ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  void* BOOL ;

/* Variables and functions */
 void* CRYPT_AsnDecodeIntInternal (int /*<<< orphan*/  const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 void* TRUE ; 

__attribute__((used)) static BOOL CRYPT_AsnDecodePathLenConstraint(const BYTE *pbEncoded,
 DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo, DWORD *pcbStructInfo,
 DWORD *pcbDecoded)
{
    BOOL ret = TRUE;
    DWORD bytesNeeded = sizeof(struct PATH_LEN_CONSTRAINT), size;

    TRACE("%p, %d, %08x, %p, %d, %p\n", pbEncoded, cbEncoded, dwFlags,
     pvStructInfo, *pcbStructInfo, pcbDecoded);

    if (!pvStructInfo)
    {
        ret = CRYPT_AsnDecodeIntInternal(pbEncoded, cbEncoded, dwFlags, NULL,
         &size, pcbDecoded);
        *pcbStructInfo = bytesNeeded;
    }
    else if (*pcbStructInfo < bytesNeeded)
    {
        SetLastError(ERROR_MORE_DATA);
        *pcbStructInfo = bytesNeeded;
        ret = FALSE;
    }
    else
    {
        struct PATH_LEN_CONSTRAINT *constraint = pvStructInfo;

        *pcbStructInfo = bytesNeeded;
        size = sizeof(constraint->dwPathLenConstraint);
        ret = CRYPT_AsnDecodeIntInternal(pbEncoded, cbEncoded, dwFlags,
         &constraint->dwPathLenConstraint, &size, pcbDecoded);
        if (ret)
            constraint->fPathLenConstraint = TRUE;
        TRACE("got an int, dwPathLenConstraint is %d\n",
         constraint->dwPathLenConstraint);
    }
    TRACE("returning %d (%08x)\n", ret, GetLastError());
    return ret;
}