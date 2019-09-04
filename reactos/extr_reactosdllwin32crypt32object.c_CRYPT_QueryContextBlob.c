#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ (* addEncodedToStore ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**) ;} ;
struct TYPE_8__ {scalar_t__ (* addEncodedToStore ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**) ;} ;
struct TYPE_7__ {scalar_t__ (* addEncodedToStore ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int DWORD ;
typedef  TYPE_1__ CERT_BLOB ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CERT_QUERY_CONTENT_CERT ; 
 int CERT_QUERY_CONTENT_CRL ; 
 int CERT_QUERY_CONTENT_CTL ; 
 int CERT_QUERY_CONTENT_FLAG_CERT ; 
 int CERT_QUERY_CONTENT_FLAG_CRL ; 
 int CERT_QUERY_CONTENT_FLAG_CTL ; 
 int /*<<< orphan*/  CERT_STORE_ADD_ALWAYS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 TYPE_4__* pCRLInterface ; 
 TYPE_3__* pCTLInterface ; 
 TYPE_2__* pCertInterface ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**) ; 

__attribute__((used)) static BOOL CRYPT_QueryContextBlob(const CERT_BLOB *blob,
 DWORD dwExpectedContentTypeFlags, HCERTSTORE store,
 DWORD *contentType, const void **ppvContext)
{
    BOOL ret = FALSE;

    if (dwExpectedContentTypeFlags & CERT_QUERY_CONTENT_FLAG_CERT)
    {
        ret = pCertInterface->addEncodedToStore(store, X509_ASN_ENCODING,
         blob->pbData, blob->cbData, CERT_STORE_ADD_ALWAYS, ppvContext);
        if (ret && contentType)
            *contentType = CERT_QUERY_CONTENT_CERT;
    }
    if (!ret && (dwExpectedContentTypeFlags & CERT_QUERY_CONTENT_FLAG_CRL))
    {
        ret = pCRLInterface->addEncodedToStore(store, X509_ASN_ENCODING,
         blob->pbData, blob->cbData, CERT_STORE_ADD_ALWAYS, ppvContext);
        if (ret && contentType)
            *contentType = CERT_QUERY_CONTENT_CRL;
    }
    if (!ret && (dwExpectedContentTypeFlags & CERT_QUERY_CONTENT_FLAG_CTL))
    {
        ret = pCTLInterface->addEncodedToStore(store, X509_ASN_ENCODING,
         blob->pbData, blob->cbData, CERT_STORE_ADD_ALWAYS, ppvContext);
        if (ret && contentType)
            *contentType = CERT_QUERY_CONTENT_CTL;
    }
    return ret;
}