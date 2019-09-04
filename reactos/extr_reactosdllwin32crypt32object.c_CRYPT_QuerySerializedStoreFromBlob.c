#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pbData; int /*<<< orphan*/  cbData; } ;
typedef  int /*<<< orphan*/  HCRYPTMSG ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_QUERY_CONTENT_SERIALIZED_STORE ; 
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 scalar_t__ CRYPT_ReadSerializedStoreFromBlob (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertDuplicateStore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

__attribute__((used)) static BOOL CRYPT_QuerySerializedStoreFromBlob(const CRYPT_DATA_BLOB *blob,
 DWORD *pdwMsgAndCertEncodingType, DWORD *pdwContentType,
 HCERTSTORE *phCertStore, HCRYPTMSG *phMsg)
{
    HCERTSTORE store = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    BOOL ret;

    TRACE("(%d, %p)\n", blob->cbData, blob->pbData);

    ret = CRYPT_ReadSerializedStoreFromBlob(blob, store);
    if (ret)
    {
        if (pdwMsgAndCertEncodingType)
            *pdwMsgAndCertEncodingType = X509_ASN_ENCODING;
        if (pdwContentType)
            *pdwContentType = CERT_QUERY_CONTENT_SERIALIZED_STORE;
        if (phCertStore)
            *phCertStore = CertDuplicateStore(store);
    }
    CertCloseStore(store, 0);
    TRACE("returning %d\n", ret);
    return ret;
}