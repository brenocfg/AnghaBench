#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cbData; int /*<<< orphan*/ * pbData; } ;
typedef  int DWORD ;
typedef  TYPE_1__ CRYPT_BIT_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_AsnDecodeBitsInternal (int /*<<< orphan*/  const*,int,int,void*,int*,int*) ; 
 int CRYPT_DECODE_NOCOPY_FLAG ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static BOOL CRYPT_AsnDecodeBitsSwapBytes(const BYTE *pbEncoded,
 DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo, DWORD *pcbStructInfo,
 DWORD *pcbDecoded)
{
    BOOL ret;

    TRACE("(%p, %d, 0x%08x, %p, %d, %p)\n", pbEncoded, cbEncoded, dwFlags,
     pvStructInfo, *pcbStructInfo, pcbDecoded);

    /* Can't use the CRYPT_DECODE_NOCOPY_FLAG, because we modify the bytes in-
     * place.
     */
    ret = CRYPT_AsnDecodeBitsInternal(pbEncoded, cbEncoded,
     dwFlags & ~CRYPT_DECODE_NOCOPY_FLAG, pvStructInfo, pcbStructInfo,
     pcbDecoded);
    if (ret && pvStructInfo)
    {
        CRYPT_BIT_BLOB *blob = pvStructInfo;

        if (blob->cbData)
        {
            DWORD i;
            BYTE temp;

            for (i = 0; i < blob->cbData / 2; i++)
            {
                temp = blob->pbData[i];
                blob->pbData[i] = blob->pbData[blob->cbData - i - 1];
                blob->pbData[blob->cbData - i - 1] = temp;
            }
        }
    }
    TRACE("returning %d (%08x)\n", ret, GetLastError());
    return ret;
}