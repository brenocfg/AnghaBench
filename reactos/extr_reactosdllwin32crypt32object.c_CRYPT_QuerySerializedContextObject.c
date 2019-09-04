#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINE_CONTEXT_INTERFACE ;
struct TYPE_3__ {int /*<<< orphan*/  pbData; int /*<<< orphan*/  cbData; } ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int DWORD ;
typedef  TYPE_1__ const CERT_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_CONTEXT ; 
 int CERT_QUERY_CONTENT_FLAG_SERIALIZED_CERT ; 
 int CERT_QUERY_CONTENT_FLAG_SERIALIZED_CRL ; 
 int CERT_QUERY_CONTENT_FLAG_SERIALIZED_CTL ; 
 int CERT_QUERY_CONTENT_SERIALIZED_CERT ; 
 int CERT_QUERY_CONTENT_SERIALIZED_CRL ; 
 int CERT_QUERY_CONTENT_SERIALIZED_CTL ; 
#define  CERT_QUERY_OBJECT_BLOB 132 
#define  CERT_QUERY_OBJECT_FILE 131 
 int /*<<< orphan*/  CERT_STORE_ALL_CONTEXT_FLAG ; 
#define  CERT_STORE_CERTIFICATE_CONTEXT 130 
#define  CERT_STORE_CRL_CONTEXT 129 
#define  CERT_STORE_CTL_CONTEXT 128 
 int /*<<< orphan*/  CRL_CONTEXT ; 
 scalar_t__ CRYPT_ReadBlobFromFile (void const*,TYPE_1__ const*) ; 
 void* CRYPT_ReadSerializedElement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CTL_CONTEXT ; 
 int /*<<< orphan*/  CertDuplicateStore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Context_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Context_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int X509_ASN_ENCODING ; 
 int /*<<< orphan*/  context_from_ptr (void const*) ; 
 int /*<<< orphan*/  hCertStore ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pCRLInterface ; 
 int /*<<< orphan*/ * pCTLInterface ; 
 int /*<<< orphan*/ * pCertInterface ; 

__attribute__((used)) static BOOL CRYPT_QuerySerializedContextObject(DWORD dwObjectType,
 const void *pvObject, DWORD dwExpectedContentTypeFlags,
 DWORD *pdwMsgAndCertEncodingType, DWORD *pdwContentType,
 HCERTSTORE *phCertStore, const void **ppvContext)
{
    CERT_BLOB fileBlob;
    const CERT_BLOB *blob;
    const WINE_CONTEXT_INTERFACE *contextInterface = NULL;
    const void *context;
    DWORD contextType;
    BOOL ret;

    switch (dwObjectType)
    {
    case CERT_QUERY_OBJECT_FILE:
        /* Cert, CRL, and CTL contexts can't be "embedded" in a file, so
         * just read the file directly
         */
        ret = CRYPT_ReadBlobFromFile(pvObject, &fileBlob);
        blob = &fileBlob;
        break;
    case CERT_QUERY_OBJECT_BLOB:
        blob = pvObject;
        ret = TRUE;
        break;
    default:
        SetLastError(E_INVALIDARG); /* FIXME: is this the correct error? */
        ret = FALSE;
    }
    if (!ret)
        return FALSE;

    ret = FALSE;
    context = CRYPT_ReadSerializedElement(blob->pbData, blob->cbData,
     CERT_STORE_ALL_CONTEXT_FLAG, &contextType);
    if (context)
    {
        DWORD contentType, certStoreOffset;

        ret = TRUE;
        switch (contextType)
        {
        case CERT_STORE_CERTIFICATE_CONTEXT:
            contextInterface = pCertInterface;
            contentType = CERT_QUERY_CONTENT_SERIALIZED_CERT;
            certStoreOffset = offsetof(CERT_CONTEXT, hCertStore);
            if (!(dwExpectedContentTypeFlags &
             CERT_QUERY_CONTENT_FLAG_SERIALIZED_CERT))
            {
                SetLastError(ERROR_INVALID_DATA);
                ret = FALSE;
                goto end;
            }
            break;
        case CERT_STORE_CRL_CONTEXT:
            contextInterface = pCRLInterface;
            contentType = CERT_QUERY_CONTENT_SERIALIZED_CRL;
            certStoreOffset = offsetof(CRL_CONTEXT, hCertStore);
            if (!(dwExpectedContentTypeFlags &
             CERT_QUERY_CONTENT_FLAG_SERIALIZED_CRL))
            {
                SetLastError(ERROR_INVALID_DATA);
                ret = FALSE;
                goto end;
            }
            break;
        case CERT_STORE_CTL_CONTEXT:
            contextInterface = pCTLInterface;
            contentType = CERT_QUERY_CONTENT_SERIALIZED_CTL;
            certStoreOffset = offsetof(CTL_CONTEXT, hCertStore);
            if (!(dwExpectedContentTypeFlags &
             CERT_QUERY_CONTENT_FLAG_SERIALIZED_CTL))
            {
                SetLastError(ERROR_INVALID_DATA);
                ret = FALSE;
                goto end;
            }
            break;
        default:
            SetLastError(ERROR_INVALID_DATA);
            ret = FALSE;
            goto end;
        }
        if (pdwMsgAndCertEncodingType)
            *pdwMsgAndCertEncodingType = X509_ASN_ENCODING;
        if (pdwContentType)
            *pdwContentType = contentType;
        if (phCertStore)
            *phCertStore = CertDuplicateStore(
             *(HCERTSTORE *)((const BYTE *)context + certStoreOffset));
        if (ppvContext)
        {
            *ppvContext = context;
            Context_AddRef(context_from_ptr(context));
        }
    }

end:
    if (contextInterface && context)
        Context_Release(context_from_ptr(context));
    if (blob == &fileBlob)
        CryptMemFree(blob->pbData);
    TRACE("returning %d\n", ret);
    return ret;
}