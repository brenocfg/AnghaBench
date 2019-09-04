#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
struct TYPE_9__ {int member_0; int /*<<< orphan*/ * member_1; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwCertEncodingType; } ;
typedef  TYPE_1__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int DWORD ;
typedef  TYPE_2__ CRYPT_HASH_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_FIND_SHA1_HASH ; 
 int /*<<< orphan*/  CERT_HASH_PROP_ID ; 
 TYPE_1__* CertFindCertificateInStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CertGetCertificateContextProperty (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static PCCERT_CONTEXT CRYPT_FindCertInStore(HCERTSTORE store,
 PCCERT_CONTEXT cert)
{
    PCCERT_CONTEXT matching = NULL;
    BYTE hash[20];
    DWORD size = sizeof(hash);

    if (CertGetCertificateContextProperty(cert, CERT_HASH_PROP_ID, hash, &size))
    {
        CRYPT_HASH_BLOB blob = { sizeof(hash), hash };

        matching = CertFindCertificateInStore(store, cert->dwCertEncodingType,
         0, CERT_FIND_SHA1_HASH, &blob, NULL);
    }
    return matching;
}