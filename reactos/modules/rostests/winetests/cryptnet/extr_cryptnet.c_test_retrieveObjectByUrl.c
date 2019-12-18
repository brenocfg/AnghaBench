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
typedef  int /*<<< orphan*/  certWithCRLDistPoint ;
typedef  int /*<<< orphan*/  aux ;
struct TYPE_9__ {int cBlob; TYPE_1__* rgBlob; } ;
struct TYPE_8__ {int cbSize; TYPE_2__* pLastSyncTime; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int cbData; } ;
typedef  int /*<<< orphan*/ * PCCRL_CONTEXT ;
typedef  scalar_t__ PCCERT_CONTEXT ;
typedef  scalar_t__ HCERTSTORE ;
typedef  TYPE_2__ FILETIME ;
typedef  int DWORD ;
typedef  TYPE_3__ CRYPT_RETRIEVE_AUX_INFO ;
typedef  TYPE_4__ CRYPT_BLOB_ARRAY ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CONTEXT_OID_CAPI2_ANY ; 
 int /*<<< orphan*/ * CONTEXT_OID_CERTIFICATE ; 
 int /*<<< orphan*/ * CONTEXT_OID_CRL ; 
 int /*<<< orphan*/  CRYPT_CACHE_ONLY_RETRIEVAL ; 
 int CRYPT_E_ASN1_BADTAG ; 
 int CRYPT_E_NO_MATCH ; 
 int /*<<< orphan*/  CertCloseStore (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CertEnumCertificatesInStore (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CertFreeCRLContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertFreeCertificateContext (scalar_t__) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_4__*) ; 
 int CryptRetrieveObjectByUrlA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_PATH_NOT_FOUND ; 
 int E_INVALIDARG ; 
 int GetLastError () ; 
 int MAX_PATH ; 
 int OSS_DATA_ERROR ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  make_tmp_file (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_retrieveObjectByUrl(void)
{
    BOOL ret;
    char tmpfile[MAX_PATH], url[MAX_PATH + 8];
    CRYPT_BLOB_ARRAY *pBlobArray;
    PCCERT_CONTEXT cert;
    PCCRL_CONTEXT crl;
    HCERTSTORE store;
    CRYPT_RETRIEVE_AUX_INFO aux = { 0 };
    FILETIME ft = { 0 };

    SetLastError(0xdeadbeef);
    ret = CryptRetrieveObjectByUrlA(NULL, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL);
    ok(!ret && (GetLastError() == ERROR_INVALID_PARAMETER ||
                GetLastError() == E_INVALIDARG),
       "got 0x%x/%u (expected ERROR_INVALID_PARAMETER or E_INVALIDARG)\n",
       GetLastError(), GetLastError());

    make_tmp_file(tmpfile);
    sprintf(url, "file://%s", tmpfile);

    pBlobArray = (CRYPT_BLOB_ARRAY *)0xdeadbeef;
    ret = CryptRetrieveObjectByUrlA(url, NULL, 0, 0, (void **)&pBlobArray,
     NULL, NULL, NULL, NULL);
    if (!ret)
    {
        /* File URL support was apparently removed in Vista/Windows 2008 */
        win_skip("File URLs not supported\n");
        return;
    }
    ok(ret, "CryptRetrieveObjectByUrlA failed: %d\n", GetLastError());
    ok(pBlobArray && pBlobArray != (CRYPT_BLOB_ARRAY *)0xdeadbeef,
     "Expected a valid pointer\n");
    if (pBlobArray && pBlobArray != (CRYPT_BLOB_ARRAY *)0xdeadbeef)
    {
        ok(pBlobArray->cBlob == 1, "Expected 1 blob, got %d\n",
         pBlobArray->cBlob);
        ok(pBlobArray->rgBlob[0].cbData == sizeof(certWithCRLDistPoint),
         "Unexpected size %d\n", pBlobArray->rgBlob[0].cbData);
        CryptMemFree(pBlobArray);
    }
    cert = (PCCERT_CONTEXT)0xdeadbeef;
    ret = CryptRetrieveObjectByUrlA(url, CONTEXT_OID_CERTIFICATE, 0, 0,
     (void **)&cert, NULL, NULL, NULL, NULL);
    ok(ret, "CryptRetrieveObjectByUrlA failed: %d\n", GetLastError());
    ok(cert && cert != (PCCERT_CONTEXT)0xdeadbeef, "Expected a cert\n");
    if (cert && cert != (PCCERT_CONTEXT)0xdeadbeef)
        CertFreeCertificateContext(cert);
    crl = (PCCRL_CONTEXT)0xdeadbeef;
    SetLastError(0xdeadbeef);
    ret = CryptRetrieveObjectByUrlA(url, CONTEXT_OID_CRL, 0, 0, (void **)&crl,
     NULL, NULL, NULL, NULL);
    /* w2k3,XP, newer w2k: CRYPT_E_NO_MATCH, older w2k: CRYPT_E_ASN1_BADTAG
     * or OSS_DATA_ERROR.
     */
    ok(!ret && (GetLastError() == CRYPT_E_NO_MATCH ||
                broken(GetLastError() == CRYPT_E_ASN1_BADTAG ||
                       GetLastError() == OSS_DATA_ERROR)),
        "got 0x%x/%u (expected CRYPT_E_NO_MATCH)\n", GetLastError(), GetLastError());

    /* only newer versions of cryptnet do the cleanup */
    if(!ret && GetLastError() != CRYPT_E_ASN1_BADTAG &&
               GetLastError() != OSS_DATA_ERROR) {
        ok(crl == NULL, "Expected CRL to be NULL\n");
    }

    if (crl && crl != (PCCRL_CONTEXT)0xdeadbeef)
        CertFreeCRLContext(crl);
    store = (HCERTSTORE)0xdeadbeef;
    ret = CryptRetrieveObjectByUrlA(url, CONTEXT_OID_CAPI2_ANY, 0, 0,
     &store, NULL, NULL, NULL, NULL);
    ok(ret, "CryptRetrieveObjectByUrlA failed: %d\n", GetLastError());
    if (store && store != (HCERTSTORE)0xdeadbeef)
    {
        DWORD certs = 0;

        cert = NULL;
        do {
            cert = CertEnumCertificatesInStore(store, cert);
            if (cert)
                certs++;
        } while (cert);
        ok(certs == 1, "Expected 1 cert, got %d\n", certs);
        CertCloseStore(store, 0);
    }
    /* Are file URLs cached? */
    cert = (PCCERT_CONTEXT)0xdeadbeef;
    ret = CryptRetrieveObjectByUrlA(url, CONTEXT_OID_CERTIFICATE,
     CRYPT_CACHE_ONLY_RETRIEVAL, 0, (void **)&cert, NULL, NULL, NULL, NULL);
    ok(ret, "CryptRetrieveObjectByUrlA failed: %08x\n", GetLastError());
    if (cert && cert != (PCCERT_CONTEXT)0xdeadbeef)
        CertFreeCertificateContext(cert);

    cert = (PCCERT_CONTEXT)0xdeadbeef;
    ret = CryptRetrieveObjectByUrlA(url, CONTEXT_OID_CERTIFICATE, 0, 0,
     (void **)&cert, NULL, NULL, NULL, &aux);
    /* w2k: failure with E_INVALIDARG */
    ok(ret || broken(GetLastError() == E_INVALIDARG),
       "got %u with 0x%x/%u (expected '!=0' or '0' with E_INVALIDARG)\n",
       ret, GetLastError(), GetLastError());
    if (cert && cert != (PCCERT_CONTEXT)0xdeadbeef)
        CertFreeCertificateContext(cert);

    cert = (PCCERT_CONTEXT)0xdeadbeef;
    aux.cbSize = sizeof(aux);
    ret = CryptRetrieveObjectByUrlA(url, CONTEXT_OID_CERTIFICATE, 0, 0,
     (void **)&cert, NULL, NULL, NULL, &aux);
    /* w2k: failure with E_INVALIDARG */
    ok(ret || broken(GetLastError() == E_INVALIDARG),
       "got %u with 0x%x/%u (expected '!=0' or '0' with E_INVALIDARG)\n",
       ret, GetLastError(), GetLastError());
    if (!ret) {
        /* no more tests useful */
        DeleteFileA(tmpfile);
        skip("no usable CertificateContext\n");
        return;
    }
    CertFreeCertificateContext(cert);

    aux.pLastSyncTime = &ft;
    ret = CryptRetrieveObjectByUrlA(url, CONTEXT_OID_CERTIFICATE, 0, 0,
     (void **)&cert, NULL, NULL, NULL, &aux);
    ok(ret, "CryptRetrieveObjectByUrlA failed: %08x\n", GetLastError());
    CertFreeCertificateContext(cert);
    ok(ft.dwLowDateTime || ft.dwHighDateTime,
     "Expected last sync time to be set\n");
    DeleteFileA(tmpfile);
    /* Okay, after being deleted, are file URLs still cached? */
    SetLastError(0xdeadbeef);
    ret = CryptRetrieveObjectByUrlA(url, CONTEXT_OID_CERTIFICATE,
     CRYPT_CACHE_ONLY_RETRIEVAL, 0, (void **)&cert, NULL, NULL, NULL, NULL);
    ok(!ret && (GetLastError() == ERROR_FILE_NOT_FOUND ||
     GetLastError() == ERROR_PATH_NOT_FOUND),
     "Expected ERROR_FILE_NOT_FOUND or ERROR_PATH_NOT_FOUND, got %d\n",
     GetLastError());
}