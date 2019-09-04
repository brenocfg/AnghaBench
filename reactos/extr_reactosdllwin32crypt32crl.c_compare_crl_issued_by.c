#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_17__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {TYPE_1__* pCrlInfo; } ;
struct TYPE_24__ {int /*<<< orphan*/  DirectoryName; } ;
struct TYPE_28__ {scalar_t__ dwAltNameChoice; TYPE_4__ u; } ;
struct TYPE_22__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_27__ {TYPE_2__ Value; } ;
struct TYPE_26__ {size_t cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_25__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Subject; } ;
struct TYPE_23__ {size_t cAltEntry; TYPE_8__* rgAltEntry; } ;
struct TYPE_21__ {int /*<<< orphan*/  rgExtension; int /*<<< orphan*/  cExtension; int /*<<< orphan*/  Issuer; } ;
struct TYPE_20__ {scalar_t__ cbData; } ;
struct TYPE_19__ {TYPE_6__ KeyId; TYPE_17__ AuthorityCertSerialNumber; TYPE_3__ AuthorityCertIssuer; } ;
struct TYPE_18__ {TYPE_5__* pCertInfo; int /*<<< orphan*/  dwCertEncodingType; } ;
typedef  TYPE_7__* PCERT_EXTENSION ;
typedef  TYPE_8__* PCERT_ALT_NAME_ENTRY ;
typedef  TYPE_9__* PCCRL_CONTEXT ;
typedef  TYPE_10__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  size_t DWORD ;
typedef  TYPE_11__ CERT_AUTHORITY_KEY_ID2_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CERT_ALT_NAME_DIRECTORY_NAME ; 
 int /*<<< orphan*/  CERT_KEY_IDENTIFIER_PROP_ID ; 
 size_t CRL_FIND_ISSUED_BY_AKI_FLAG ; 
 size_t CRL_FIND_ISSUED_BY_SIGNATURE_FLAG ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  CRYPT_VERIFY_CERT_SIGN_ISSUER_CERT ; 
 int /*<<< orphan*/  CRYPT_VERIFY_CERT_SIGN_SUBJECT_CRL ; 
 int CertCompareCertificateName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CertCompareIntegerBlob (int /*<<< orphan*/ *,TYPE_17__*) ; 
 TYPE_7__* CertFindExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CertGetCertificateContextProperty (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_11__**,size_t*) ; 
 int /*<<< orphan*/ * CryptMemAlloc (size_t) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int CryptVerifyCertificateSignatureEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  LocalFree (TYPE_11__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_AUTHORITY_KEY_ID2 ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  szOID_AUTHORITY_KEY_IDENTIFIER2 ; 

__attribute__((used)) static BOOL compare_crl_issued_by(PCCRL_CONTEXT pCrlContext, DWORD dwType,
 DWORD dwFlags, const void *pvPara)
{
    BOOL ret;

    if (pvPara)
    {
        PCCERT_CONTEXT issuer = pvPara;

        ret = CertCompareCertificateName(issuer->dwCertEncodingType,
         &issuer->pCertInfo->Subject, &pCrlContext->pCrlInfo->Issuer);
        if (ret && (dwFlags & CRL_FIND_ISSUED_BY_SIGNATURE_FLAG))
            ret = CryptVerifyCertificateSignatureEx(0,
             issuer->dwCertEncodingType,
             CRYPT_VERIFY_CERT_SIGN_SUBJECT_CRL, (void *)pCrlContext,
             CRYPT_VERIFY_CERT_SIGN_ISSUER_CERT, (void *)issuer, 0, NULL);
        if (ret && (dwFlags & CRL_FIND_ISSUED_BY_AKI_FLAG))
        {
            PCERT_EXTENSION ext = CertFindExtension(
             szOID_AUTHORITY_KEY_IDENTIFIER2, pCrlContext->pCrlInfo->cExtension,
             pCrlContext->pCrlInfo->rgExtension);

            if (ext)
            {
                CERT_AUTHORITY_KEY_ID2_INFO *info;
                DWORD size;

                if ((ret = CryptDecodeObjectEx(X509_ASN_ENCODING,
                 X509_AUTHORITY_KEY_ID2, ext->Value.pbData, ext->Value.cbData,
                 CRYPT_DECODE_ALLOC_FLAG, NULL, &info, &size)))
                {
                    if (info->AuthorityCertIssuer.cAltEntry &&
                     info->AuthorityCertSerialNumber.cbData)
                    {
                        PCERT_ALT_NAME_ENTRY directoryName = NULL;
                        DWORD i;

                        for (i = 0; !directoryName &&
                         i < info->AuthorityCertIssuer.cAltEntry; i++)
                            if (info->AuthorityCertIssuer.rgAltEntry[i].
                             dwAltNameChoice == CERT_ALT_NAME_DIRECTORY_NAME)
                                directoryName =
                                 &info->AuthorityCertIssuer.rgAltEntry[i];
                        if (directoryName)
                        {
                            ret = CertCompareCertificateName(
                             issuer->dwCertEncodingType,
                             &issuer->pCertInfo->Subject,
                             &directoryName->u.DirectoryName);
                            if (ret)
                                ret = CertCompareIntegerBlob(
                                 &issuer->pCertInfo->SerialNumber,
                                 &info->AuthorityCertSerialNumber);
                        }
                        else
                        {
                            FIXME("no supported name type in authority key id2\n");
                            ret = FALSE;
                        }
                    }
                    else if (info->KeyId.cbData)
                    {
                        DWORD size;

                        ret = CertGetCertificateContextProperty(issuer,
                         CERT_KEY_IDENTIFIER_PROP_ID, NULL, &size);
                        if (ret && size == info->KeyId.cbData)
                        {
                            LPBYTE buf = CryptMemAlloc(size);

                            if (buf)
                            {
                                CertGetCertificateContextProperty(issuer,
                                 CERT_KEY_IDENTIFIER_PROP_ID, buf, &size);
                                ret = !memcmp(buf, info->KeyId.pbData, size);
                                CryptMemFree(buf);
                            }
                            else
                                ret = FALSE;
                        }
                        else
                            ret = FALSE;
                    }
                    else
                    {
                        FIXME("unsupported value for AKI extension\n");
                        ret = FALSE;
                    }
                    LocalFree(info);
                }
            }
            /* else: a CRL without an AKI matches any cert */
        }
    }
    else
        ret = TRUE;
    return ret;
}