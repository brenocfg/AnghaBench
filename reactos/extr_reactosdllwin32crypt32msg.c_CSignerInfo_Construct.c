#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  Parameters; scalar_t__ pszObjId; } ;
struct TYPE_19__ {int /*<<< orphan*/  Parameters; scalar_t__ pszObjId; } ;
struct TYPE_28__ {TYPE_12__ Algorithm; } ;
struct TYPE_29__ {TYPE_7__ SubjectPublicKeyInfo; int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_23__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_26__ {int /*<<< orphan*/  KeyId; TYPE_2__ IssuerSerialNumber; } ;
struct TYPE_27__ {scalar_t__ dwIdChoice; TYPE_5__ u; } ;
struct TYPE_22__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_24__ {int /*<<< orphan*/  KeyId; TYPE_1__ IssuerSerialNumber; } ;
struct TYPE_25__ {TYPE_3__ u; scalar_t__ dwIdChoice; } ;
struct TYPE_17__ {int /*<<< orphan*/  Parameters; int /*<<< orphan*/  pszObjId; } ;
struct TYPE_21__ {int /*<<< orphan*/  UnauthAttrs; int /*<<< orphan*/  AuthAttrs; TYPE_10__ HashAlgorithm; TYPE_9__ HashEncryptionAlgorithm; TYPE_4__ SignerId; void* dwVersion; } ;
struct TYPE_18__ {int /*<<< orphan*/  Parameters; int /*<<< orphan*/  pszObjId; } ;
struct TYPE_20__ {int cbSize; int /*<<< orphan*/  cUnauthAttr; int /*<<< orphan*/  cAuthAttr; TYPE_11__ HashAlgorithm; TYPE_8__* pCertInfo; TYPE_12__ HashEncryptionAlgorithm; TYPE_6__ SignerId; } ;
typedef  int /*<<< orphan*/  CRYPT_ATTRIBUTES ;
typedef  TYPE_12__ CRYPT_ALGORITHM_IDENTIFIER ;
typedef  TYPE_13__ CMSG_SIGNER_ENCODE_INFO_WITH_CMS ;
typedef  int /*<<< orphan*/  CMSG_SIGNER_ENCODE_INFO ;
typedef  TYPE_14__ CMSG_CMS_SIGNER_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CERT_ID_ISSUER_SERIAL_NUMBER ; 
 scalar_t__ CERT_ID_KEY_IDENTIFIER ; 
 void* CMSG_SIGNER_INFO_V1 ; 
 void* CMSG_SIGNER_INFO_V3 ; 
 scalar_t__ CRYPT_ConstructAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CRYPT_ConstructBlob (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL CSignerInfo_Construct(CMSG_CMS_SIGNER_INFO *info,
 const CMSG_SIGNER_ENCODE_INFO_WITH_CMS *in)
{
    BOOL ret;

    if (in->cbSize == sizeof(CMSG_SIGNER_ENCODE_INFO))
    {
        info->dwVersion = CMSG_SIGNER_INFO_V1;
        ret = CRYPT_ConstructBlob(&info->SignerId.u.IssuerSerialNumber.Issuer,
         &in->pCertInfo->Issuer);
        if (ret)
            ret = CRYPT_ConstructBlob(
             &info->SignerId.u.IssuerSerialNumber.SerialNumber,
             &in->pCertInfo->SerialNumber);
        info->SignerId.dwIdChoice = CERT_ID_ISSUER_SERIAL_NUMBER;
        info->HashEncryptionAlgorithm.pszObjId =
         in->pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId;
        if (ret)
            ret = CRYPT_ConstructBlob(&info->HashEncryptionAlgorithm.Parameters,
             &in->pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters);
    }
    else
    {
        const CRYPT_ALGORITHM_IDENTIFIER *pEncrAlg;

        /* Implicitly in->cbSize == sizeof(CMSG_SIGNER_ENCODE_INFO_WITH_CMS).
         * See CRYPT_IsValidSigner.
         */
        if (!in->SignerId.dwIdChoice)
        {
            info->dwVersion = CMSG_SIGNER_INFO_V1;
            ret = CRYPT_ConstructBlob(&info->SignerId.u.IssuerSerialNumber.Issuer,
             &in->pCertInfo->Issuer);
            if (ret)
                ret = CRYPT_ConstructBlob(
                 &info->SignerId.u.IssuerSerialNumber.SerialNumber,
                 &in->pCertInfo->SerialNumber);
            info->SignerId.dwIdChoice = CERT_ID_ISSUER_SERIAL_NUMBER;
        }
        else if (in->SignerId.dwIdChoice == CERT_ID_ISSUER_SERIAL_NUMBER)
        {
            info->dwVersion = CMSG_SIGNER_INFO_V1;
            info->SignerId.dwIdChoice = CERT_ID_ISSUER_SERIAL_NUMBER;
            ret = CRYPT_ConstructBlob(&info->SignerId.u.IssuerSerialNumber.Issuer,
             &in->SignerId.u.IssuerSerialNumber.Issuer);
            if (ret)
                ret = CRYPT_ConstructBlob(
                 &info->SignerId.u.IssuerSerialNumber.SerialNumber,
                 &in->SignerId.u.IssuerSerialNumber.SerialNumber);
        }
        else
        {
            /* Implicitly dwIdChoice == CERT_ID_KEY_IDENTIFIER */
            info->dwVersion = CMSG_SIGNER_INFO_V3;
            info->SignerId.dwIdChoice = CERT_ID_KEY_IDENTIFIER;
            ret = CRYPT_ConstructBlob(&info->SignerId.u.KeyId,
             &in->SignerId.u.KeyId);
        }
        pEncrAlg = in->HashEncryptionAlgorithm.pszObjId ?
         &in->HashEncryptionAlgorithm :
         &in->pCertInfo->SubjectPublicKeyInfo.Algorithm;
        info->HashEncryptionAlgorithm.pszObjId = pEncrAlg->pszObjId;
        if (ret)
            ret = CRYPT_ConstructBlob(&info->HashEncryptionAlgorithm.Parameters,
             &pEncrAlg->Parameters);
    }
    /* Assumption:  algorithm IDs will point to static strings, not
     * stack-based ones, so copying the pointer values is safe.
     */
    info->HashAlgorithm.pszObjId = in->HashAlgorithm.pszObjId;
    if (ret)
        ret = CRYPT_ConstructBlob(&info->HashAlgorithm.Parameters,
         &in->HashAlgorithm.Parameters);
    if (ret)
        ret = CRYPT_ConstructAttributes(&info->AuthAttrs,
         (CRYPT_ATTRIBUTES *)&in->cAuthAttr);
    if (ret)
        ret = CRYPT_ConstructAttributes(&info->UnauthAttrs,
         (CRYPT_ATTRIBUTES *)&in->cUnauthAttr);
    return ret;
}