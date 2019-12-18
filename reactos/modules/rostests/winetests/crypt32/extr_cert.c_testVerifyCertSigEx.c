#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ cUnusedBits; int /*<<< orphan*/ * pbData; void* cbData; } ;
struct TYPE_11__ {scalar_t__ cbData; } ;
struct TYPE_12__ {TYPE_2__ Parameters; scalar_t__ pszObjId; } ;
struct TYPE_10__ {int cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_15__ {TYPE_4__ Signature; TYPE_3__ SignatureAlgorithm; TYPE_1__ ToBeSigned; } ;
struct TYPE_14__ {int cbData; int /*<<< orphan*/ * pbData; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/ * PCERT_PUBLIC_KEY_INFO ;
typedef  scalar_t__ LPSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  void* DWORD ;
typedef  TYPE_5__ CRYPT_DATA_BLOB ;
typedef  TYPE_6__ CERT_SIGNED_CONTENT_INFO ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int /*<<< orphan*/  CRYPT_ENCODE_ALLOC_FLAG ; 
 scalar_t__ CRYPT_E_ASN1_BADTAG ; 
 scalar_t__ CRYPT_E_ASN1_EOD ; 
 int /*<<< orphan*/  CRYPT_VERIFY_CERT_SIGN_ISSUER_NULL ; 
 int /*<<< orphan*/  CRYPT_VERIFY_CERT_SIGN_ISSUER_PUBKEY ; 
 int /*<<< orphan*/  CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB ; 
 int CryptExportPublicKeyInfoEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_ACCESS_VIOLATION ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_CERT ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int pCryptEncodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void**) ; 
 int pCryptVerifyCertificateSignatureEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void testVerifyCertSigEx(HCRYPTPROV csp, const CRYPT_DATA_BLOB *toBeSigned,
 LPCSTR sigOID, const BYTE *sig, DWORD sigLen)
{
    CERT_SIGNED_CONTENT_INFO info;
    LPBYTE cert = NULL;
    DWORD size = 0;
    BOOL ret;

    if (!pCryptVerifyCertificateSignatureEx)
    {
        win_skip("no CryptVerifyCertificateSignatureEx support\n");
        return;
    }
    if (!pCryptEncodeObjectEx)
    {
        win_skip("no CryptEncodeObjectEx support\n");
        return;
    }
    ret = pCryptVerifyCertificateSignatureEx(0, 0, 0, NULL, 0, NULL, 0, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %08x\n", GetLastError());
    ret = pCryptVerifyCertificateSignatureEx(csp, 0, 0, NULL, 0, NULL, 0, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %08x\n", GetLastError());
    ret = pCryptVerifyCertificateSignatureEx(csp, X509_ASN_ENCODING, 0, NULL, 0,
     NULL, 0, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %08x\n", GetLastError());
    /* This crashes
    ret = pCryptVerifyCertificateSignatureEx(csp, X509_ASN_ENCODING,
     CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB, NULL, 0, NULL, 0, NULL);
     */
    info.ToBeSigned.cbData = toBeSigned->cbData;
    info.ToBeSigned.pbData = toBeSigned->pbData;
    info.SignatureAlgorithm.pszObjId = (LPSTR)sigOID;
    info.SignatureAlgorithm.Parameters.cbData = 0;
    info.Signature.cbData = sigLen;
    info.Signature.pbData = (BYTE *)sig;
    info.Signature.cUnusedBits = 0;
    ret = pCryptEncodeObjectEx(X509_ASN_ENCODING, X509_CERT, &info,
     CRYPT_ENCODE_ALLOC_FLAG, NULL, &cert, &size);
    ok(ret, "CryptEncodeObjectEx failed: %08x\n", GetLastError());
    if (cert)
    {
        CRYPT_DATA_BLOB certBlob = { 0, NULL };
        PCERT_PUBLIC_KEY_INFO pubKeyInfo = NULL;

        ret = pCryptVerifyCertificateSignatureEx(csp, X509_ASN_ENCODING,
         CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB, &certBlob, 0, NULL, 0, NULL);
        ok(!ret && GetLastError() == CRYPT_E_ASN1_EOD,
         "Expected CRYPT_E_ASN1_EOD, got %08x\n", GetLastError());
        certBlob.cbData = 1;
        certBlob.pbData = (void *)0xdeadbeef;
        ret = pCryptVerifyCertificateSignatureEx(csp, X509_ASN_ENCODING,
         CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB, &certBlob, 0, NULL, 0, NULL);
        ok(!ret && (GetLastError() == STATUS_ACCESS_VIOLATION ||
                    GetLastError() == CRYPT_E_ASN1_EOD /* Win9x */ ||
                    GetLastError() == CRYPT_E_ASN1_BADTAG /* Win98 */),
         "Expected STATUS_ACCESS_VIOLATION, CRYPT_E_ASN1_EOD, OR CRYPT_E_ASN1_BADTAG, got %08x\n",
         GetLastError());

        certBlob.cbData = size;
        certBlob.pbData = cert;
        ret = pCryptVerifyCertificateSignatureEx(csp, X509_ASN_ENCODING,
         CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB, &certBlob, 0, NULL, 0, NULL);
        ok(!ret && GetLastError() == E_INVALIDARG,
         "Expected E_INVALIDARG, got %08x\n", GetLastError());
        ret = pCryptVerifyCertificateSignatureEx(csp, X509_ASN_ENCODING,
         CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB, &certBlob,
         CRYPT_VERIFY_CERT_SIGN_ISSUER_NULL, NULL, 0, NULL);
        ok(!ret && GetLastError() == E_INVALIDARG,
         "Expected E_INVALIDARG, got %08x\n", GetLastError());
        /* This crashes
        ret = pCryptVerifyCertificateSignatureEx(csp, X509_ASN_ENCODING,
         CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB, &certBlob,
         CRYPT_VERIFY_CERT_SIGN_ISSUER_PUBKEY, NULL, 0, NULL);
         */
        CryptExportPublicKeyInfoEx(csp, AT_SIGNATURE, X509_ASN_ENCODING,
         (LPSTR)sigOID, 0, NULL, NULL, &size);
        pubKeyInfo = HeapAlloc(GetProcessHeap(), 0, size);
        if (pubKeyInfo)
        {
            ret = CryptExportPublicKeyInfoEx(csp, AT_SIGNATURE,
             X509_ASN_ENCODING, (LPSTR)sigOID, 0, NULL, pubKeyInfo, &size);
            ok(ret, "CryptExportKey failed: %08x\n", GetLastError());
            if (ret)
            {
                ret = pCryptVerifyCertificateSignatureEx(csp, X509_ASN_ENCODING,
                 CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB, &certBlob,
                 CRYPT_VERIFY_CERT_SIGN_ISSUER_PUBKEY, pubKeyInfo, 0, NULL);
                ok(ret, "CryptVerifyCertificateSignatureEx failed: %08x\n",
                 GetLastError());
            }
            HeapFree(GetProcessHeap(), 0, pubKeyInfo);
        }
        LocalFree(cert);
    }
}