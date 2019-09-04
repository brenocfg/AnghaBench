#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ cbData; } ;
struct TYPE_17__ {TYPE_1__ Parameters; scalar_t__ pszObjId; } ;
struct TYPE_16__ {scalar_t__ cbData; } ;
struct TYPE_11__ {TYPE_8__ SerialNumber; TYPE_8__ Issuer; } ;
struct TYPE_12__ {int /*<<< orphan*/  KeyId; TYPE_2__ IssuerSerialNumber; } ;
struct TYPE_13__ {scalar_t__ dwIdChoice; TYPE_3__ u; } ;
struct TYPE_15__ {int /*<<< orphan*/  UnauthAttrs; int /*<<< orphan*/  AuthAttrs; TYPE_8__ EncryptedHash; TYPE_9__ HashEncryptionAlgorithm; TYPE_9__ HashAlgorithm; TYPE_4__ SignerId; int /*<<< orphan*/  dwVersion; } ;
struct TYPE_14__ {int /*<<< orphan*/  UnauthAttrs; int /*<<< orphan*/  AuthAttrs; int /*<<< orphan*/  EncryptedHash; int /*<<< orphan*/  HashEncryptionAlgorithm; int /*<<< orphan*/  HashAlgorithm; int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; int /*<<< orphan*/  dwVersion; } ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_5__ CMSG_SIGNER_INFO ;
typedef  TYPE_6__ CMSG_CMS_SIGNER_INFO ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ALIGN_DWORD_PTR (scalar_t__) ; 
 scalar_t__ CERT_ID_ISSUER_SERIAL_NUMBER ; 
 int /*<<< orphan*/  CRYPT_CopyAlgorithmId (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CRYPT_CopyAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CRYPT_CopyBlob (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CRYPT_CopyKeyIdAsIssuerAndSerial (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ CRYPT_SizeOfAttributes (int /*<<< orphan*/ *) ; 
 scalar_t__ CRYPT_SizeOfKeyIdAsIssuerAndSerial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * POINTER_ALIGN_DWORD_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static BOOL CRYPT_CopySignerInfo(void *pvData, DWORD *pcbData,
 const CMSG_CMS_SIGNER_INFO *in)
{
    DWORD size = sizeof(CMSG_SIGNER_INFO), rdnSize = 0;
    BOOL ret;

    TRACE("(%p, %d, %p)\n", pvData, pvData ? *pcbData : 0, in);

    if (in->SignerId.dwIdChoice == CERT_ID_ISSUER_SERIAL_NUMBER)
    {
        size += in->SignerId.u.IssuerSerialNumber.Issuer.cbData;
        size += in->SignerId.u.IssuerSerialNumber.SerialNumber.cbData;
    }
    else
    {
        rdnSize = CRYPT_SizeOfKeyIdAsIssuerAndSerial(&in->SignerId.u.KeyId);
        size += rdnSize;
    }
    if (in->HashAlgorithm.pszObjId)
        size += strlen(in->HashAlgorithm.pszObjId) + 1;
    size += in->HashAlgorithm.Parameters.cbData;
    if (in->HashEncryptionAlgorithm.pszObjId)
        size += strlen(in->HashEncryptionAlgorithm.pszObjId) + 1;
    size += in->HashEncryptionAlgorithm.Parameters.cbData;
    size += in->EncryptedHash.cbData;
    /* align pointer */
    size = ALIGN_DWORD_PTR(size);
    size += CRYPT_SizeOfAttributes(&in->AuthAttrs);
    size += CRYPT_SizeOfAttributes(&in->UnauthAttrs);
    if (!pvData)
    {
        ret = TRUE;
    }
    else if (*pcbData < size)
    {
        SetLastError(ERROR_MORE_DATA);
        ret = FALSE;
    }
    else
    {
        LPBYTE nextData = (BYTE *)pvData + sizeof(CMSG_SIGNER_INFO);
        CMSG_SIGNER_INFO *out = pvData;

        ret = TRUE;
        out->dwVersion = in->dwVersion;
        if (in->SignerId.dwIdChoice == CERT_ID_ISSUER_SERIAL_NUMBER)
        {
            CRYPT_CopyBlob(&out->Issuer,
             &in->SignerId.u.IssuerSerialNumber.Issuer, &nextData);
            CRYPT_CopyBlob(&out->SerialNumber,
             &in->SignerId.u.IssuerSerialNumber.SerialNumber, &nextData);
        }
        else
            ret = CRYPT_CopyKeyIdAsIssuerAndSerial(&out->Issuer, &out->SerialNumber,
             &in->SignerId.u.KeyId, rdnSize, &nextData);
        if (ret)
        {
            CRYPT_CopyAlgorithmId(&out->HashAlgorithm, &in->HashAlgorithm,
             &nextData);
            CRYPT_CopyAlgorithmId(&out->HashEncryptionAlgorithm,
             &in->HashEncryptionAlgorithm, &nextData);
            CRYPT_CopyBlob(&out->EncryptedHash, &in->EncryptedHash, &nextData);
            nextData = POINTER_ALIGN_DWORD_PTR(nextData);
            CRYPT_CopyAttributes(&out->AuthAttrs, &in->AuthAttrs, &nextData);
            CRYPT_CopyAttributes(&out->UnauthAttrs, &in->UnauthAttrs, &nextData);
        }
    }
    *pcbData = size;
    TRACE("returning %d\n", ret);
    return ret;
}