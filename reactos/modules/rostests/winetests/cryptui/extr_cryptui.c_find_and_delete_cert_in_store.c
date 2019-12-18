#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_11__ {TYPE_1__ IssuerSerialNumber; } ;
struct TYPE_14__ {TYPE_2__ u; int /*<<< orphan*/  dwIdChoice; } ;
struct TYPE_13__ {TYPE_3__* pCertInfo; } ;
struct TYPE_12__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
typedef  TYPE_4__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  CRYPT_INTEGER_BLOB ;
typedef  int /*<<< orphan*/  CERT_NAME_BLOB ;
typedef  TYPE_5__ CERT_ID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_FIND_CERT_ID ; 
 int /*<<< orphan*/  CERT_ID_ISSUER_SERIAL_NUMBER ; 
 int /*<<< orphan*/  CertDeleteCertificateFromStore (TYPE_4__*) ; 
 TYPE_4__* CertFindCertificateInStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL find_and_delete_cert_in_store(HCERTSTORE store, PCCERT_CONTEXT cert)
{
    CERT_ID id;
    PCCERT_CONTEXT found;

    id.dwIdChoice = CERT_ID_ISSUER_SERIAL_NUMBER;
    memcpy(&id.u.IssuerSerialNumber.Issuer,
     &cert->pCertInfo->Issuer, sizeof(CERT_NAME_BLOB));
    memcpy(&id.u.IssuerSerialNumber.SerialNumber,
     &cert->pCertInfo->SerialNumber, sizeof(CRYPT_INTEGER_BLOB));
    found = CertFindCertificateInStore(store, X509_ASN_ENCODING, 0,
     CERT_FIND_CERT_ID, &id, NULL);
    if (!found)
        return FALSE;

    CertDeleteCertificateFromStore(found);

    return TRUE;
}