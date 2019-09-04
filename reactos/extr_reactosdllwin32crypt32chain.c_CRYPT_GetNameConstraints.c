#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_8__ {TYPE_1__ Value; } ;
struct TYPE_7__ {int /*<<< orphan*/  rgExtension; int /*<<< orphan*/  cExtension; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CERT_NAME_CONSTRAINTS_INFO ;
typedef  TYPE_2__ CERT_INFO ;
typedef  TYPE_3__ CERT_EXTENSION ;

/* Variables and functions */
 int CRYPT_DECODE_ALLOC_FLAG ; 
 int CRYPT_DECODE_NOCOPY_FLAG ; 
 TYPE_3__* CertFindExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_NAME_CONSTRAINTS ; 
 int /*<<< orphan*/  szOID_NAME_CONSTRAINTS ; 

__attribute__((used)) static CERT_NAME_CONSTRAINTS_INFO *CRYPT_GetNameConstraints(CERT_INFO *cert)
{
    CERT_NAME_CONSTRAINTS_INFO *info = NULL;

    CERT_EXTENSION *ext;

    if ((ext = CertFindExtension(szOID_NAME_CONSTRAINTS, cert->cExtension,
     cert->rgExtension)))
    {
        DWORD size;

        CryptDecodeObjectEx(X509_ASN_ENCODING, X509_NAME_CONSTRAINTS,
         ext->Value.pbData, ext->Value.cbData,
         CRYPT_DECODE_ALLOC_FLAG | CRYPT_DECODE_NOCOPY_FLAG, NULL, &info,
         &size);
    }
    return info;
}