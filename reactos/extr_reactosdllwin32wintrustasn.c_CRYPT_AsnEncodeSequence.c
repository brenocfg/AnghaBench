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
struct AsnEncodeSequenceItem {size_t size; int /*<<< orphan*/  pvStructInfo; int /*<<< orphan*/  (* encodeFunc ) (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ;} ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_SEQUENCE ; 
 int /*<<< orphan*/  CRYPT_EncodeLen (size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct AsnEncodeSequenceItem*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  stub2 (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static BOOL CRYPT_AsnEncodeSequence(DWORD dwCertEncodingType,
 struct AsnEncodeSequenceItem items[], DWORD cItem, BYTE *pbEncoded,
 DWORD *pcbEncoded)
{
    BOOL ret;
    DWORD i, dataLen = 0;

    TRACE("%p, %d, %p, %d\n", items, cItem, pbEncoded, *pcbEncoded);
    for (i = 0, ret = TRUE; ret && i < cItem; i++)
    {
        ret = items[i].encodeFunc(dwCertEncodingType, NULL,
         items[i].pvStructInfo, NULL, &items[i].size);
        /* Some functions propagate their errors through the size */
        if (!ret)
            *pcbEncoded = items[i].size;
        dataLen += items[i].size;
    }
    if (ret)
    {
        DWORD lenBytes, bytesNeeded;

        CRYPT_EncodeLen(dataLen, NULL, &lenBytes);
        bytesNeeded = 1 + lenBytes + dataLen;
        if (!pbEncoded)
            *pcbEncoded = bytesNeeded;
        else if (*pcbEncoded < bytesNeeded)
        {
            *pcbEncoded = bytesNeeded;
            SetLastError(ERROR_MORE_DATA);
            ret = FALSE;
        }
        else
        {
            *pcbEncoded = bytesNeeded;
            *pbEncoded++ = ASN_SEQUENCE;
            CRYPT_EncodeLen(dataLen, pbEncoded, &lenBytes);
            pbEncoded += lenBytes;
            for (i = 0; ret && i < cItem; i++)
            {
                ret = items[i].encodeFunc(dwCertEncodingType, NULL,
                 items[i].pvStructInfo, pbEncoded, &items[i].size);
                /* Some functions propagate their errors through the size */
                if (!ret)
                    *pcbEncoded = items[i].size;
                pbEncoded += items[i].size;
            }
        }
    }
    TRACE("returning %d\n", ret);
    return ret;
}