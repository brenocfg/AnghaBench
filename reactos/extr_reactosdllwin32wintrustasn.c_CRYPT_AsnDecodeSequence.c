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
struct AsnDecodeSequenceItem {int size; int minSize; } ;
typedef  int DWORD ;
typedef  scalar_t__ BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ const ASN_SEQUENCE ; 
 int CRYPT_AsnDecodeSequenceItems (int,struct AsnDecodeSequenceItem*,int,scalar_t__ const*,int,int,void*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  CRYPT_E_ASN1_BADTAG ; 
 int /*<<< orphan*/  CRYPT_E_ASN1_CORRUPT ; 
 int CRYPT_GetLen (scalar_t__ const*,int,int*) ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int FALSE ; 
 int GET_LEN_BYTES (scalar_t__ const) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL CRYPT_AsnDecodeSequence(DWORD dwCertEncodingType,
 struct AsnDecodeSequenceItem items[], DWORD cItem, const BYTE *pbEncoded,
 DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo, DWORD *pcbStructInfo,
 void *startingPointer)
{
    BOOL ret;

    TRACE("%p, %d, %p, %d, %08x, %p, %d, %p\n", items, cItem, pbEncoded,
     cbEncoded, dwFlags, pvStructInfo, *pcbStructInfo, startingPointer);

    if (pbEncoded[0] == ASN_SEQUENCE)
    {
        DWORD dataLen;

        if ((ret = CRYPT_GetLen(pbEncoded, cbEncoded, &dataLen)))
        {
            DWORD lenBytes = GET_LEN_BYTES(pbEncoded[1]), cbDecoded;
            const BYTE *ptr = pbEncoded + 1 + lenBytes;

            cbEncoded -= 1 + lenBytes;
            if (cbEncoded < dataLen)
            {
                TRACE("dataLen %d exceeds cbEncoded %d, failing\n", dataLen,
                 cbEncoded);
                SetLastError(CRYPT_E_ASN1_CORRUPT);
                ret = FALSE;
            }
            else
                ret = CRYPT_AsnDecodeSequenceItems(dwFlags, items, cItem, ptr,
                 cbEncoded, dwFlags, NULL, NULL, &cbDecoded);
            if (ret && cbDecoded != dataLen)
            {
                TRACE("expected %d decoded, got %d, failing\n", dataLen,
                 cbDecoded);
                SetLastError(CRYPT_E_ASN1_CORRUPT);
                ret = FALSE;
            }
            if (ret)
            {
                DWORD i, bytesNeeded = 0, structSize = 0;

                for (i = 0; i < cItem; i++)
                {
                    bytesNeeded += items[i].size;
                    structSize += items[i].minSize;
                }
                if (!pvStructInfo)
                    *pcbStructInfo = bytesNeeded;
                else if (*pcbStructInfo < bytesNeeded)
                {
                    SetLastError(ERROR_MORE_DATA);
                    *pcbStructInfo = bytesNeeded;
                    ret = FALSE;
                }
                else
                {
                    BYTE *nextData;

                    *pcbStructInfo = bytesNeeded;
                    if (startingPointer)
                        nextData = startingPointer;
                    else
                        nextData = (BYTE *)pvStructInfo + structSize;
                    memset(pvStructInfo, 0, structSize);
                    ret = CRYPT_AsnDecodeSequenceItems(dwFlags, items, cItem,
                     ptr, cbEncoded, dwFlags, pvStructInfo, nextData,
                     &cbDecoded);
                }
            }
        }
    }
    else
    {
        SetLastError(CRYPT_E_ASN1_BADTAG);
        ret = FALSE;
    }
    TRACE("returning %d (%08x)\n", ret, GetLastError());
    return ret;
}