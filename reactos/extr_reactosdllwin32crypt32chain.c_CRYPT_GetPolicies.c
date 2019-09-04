#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* pCertInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_9__ {TYPE_2__ Value; } ;
struct TYPE_7__ {int /*<<< orphan*/  rgExtension; int /*<<< orphan*/  cExtension; } ;
typedef  TYPE_3__* PCERT_EXTENSION ;
typedef  TYPE_4__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CERT_POLICIES_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 TYPE_3__* CertFindExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_CERT_POLICIES ; 
 int /*<<< orphan*/  szOID_KEY_USAGE ; 

__attribute__((used)) static CERT_POLICIES_INFO *CRYPT_GetPolicies(PCCERT_CONTEXT cert)
{
    PCERT_EXTENSION ext;
    CERT_POLICIES_INFO *policies = NULL;

    ext = CertFindExtension(szOID_KEY_USAGE, cert->pCertInfo->cExtension,
     cert->pCertInfo->rgExtension);
    if (ext)
    {
        DWORD size;

        CryptDecodeObjectEx(X509_ASN_ENCODING, X509_CERT_POLICIES,
         ext->Value.pbData, ext->Value.cbData, CRYPT_DECODE_ALLOC_FLAG, NULL,
         &policies, &size);
    }
    return policies;
}