#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ cUnusedBits; int /*<<< orphan*/ * pbData; scalar_t__ cbData; } ;
struct TYPE_10__ {scalar_t__ cbData; } ;
struct TYPE_11__ {TYPE_2__ Parameters; scalar_t__ pszObjId; } ;
struct TYPE_9__ {int /*<<< orphan*/  pbData; int /*<<< orphan*/  cbData; } ;
struct TYPE_14__ {TYPE_4__ Signature; TYPE_3__ SignatureAlgorithm; TYPE_1__ ToBeSigned; } ;
struct TYPE_13__ {int /*<<< orphan*/  pbData; int /*<<< orphan*/  cbData; } ;
typedef  int /*<<< orphan*/ * PCERT_PUBLIC_KEY_INFO ;
typedef  scalar_t__ LPSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_5__ CRYPT_DATA_BLOB ;
typedef  TYPE_6__ CERT_SIGNED_CONTENT_INFO ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int /*<<< orphan*/  CRYPT_ENCODE_ALLOC_FLAG ; 
 scalar_t__ CRYPT_E_ASN1_EOD ; 
 int CryptExportPublicKeyInfoEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int CryptVerifyCertificateSignature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ OSS_BAD_ARG ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_CERT ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int pCryptEncodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void testVerifyCertSig(HCRYPTPROV csp, const CRYPT_DATA_BLOB *toBeSigned,
 LPCSTR sigOID, const BYTE *sig, DWORD sigLen)
{
    CERT_SIGNED_CONTENT_INFO info;
    LPBYTE cert = NULL;
    DWORD size = 0;
    BOOL ret;

    if (!pCryptEncodeObjectEx)
    {
        win_skip("no CryptEncodeObjectEx support\n");
        return;
    }
    ret = CryptVerifyCertificateSignature(0, 0, NULL, 0, NULL);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    ret = CryptVerifyCertificateSignature(csp, 0, NULL, 0, NULL);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    ret = CryptVerifyCertificateSignature(csp, X509_ASN_ENCODING, NULL, 0,
     NULL);
    ok(!ret && (GetLastError() == CRYPT_E_ASN1_EOD ||
     GetLastError() == OSS_BAD_ARG),
     "Expected CRYPT_E_ASN1_EOD or OSS_BAD_ARG, got %08x\n", GetLastError());
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
        PCERT_PUBLIC_KEY_INFO pubKeyInfo = NULL;
        DWORD pubKeySize;

        if (0)
        {
            /* Crashes prior to Vista */
            ret = CryptVerifyCertificateSignature(csp, X509_ASN_ENCODING,
             cert, size, NULL);
        }
        CryptExportPublicKeyInfoEx(csp, AT_SIGNATURE, X509_ASN_ENCODING,
         (LPSTR)sigOID, 0, NULL, NULL, &pubKeySize);
        pubKeyInfo = HeapAlloc(GetProcessHeap(), 0, pubKeySize);
        if (pubKeyInfo)
        {
            ret = CryptExportPublicKeyInfoEx(csp, AT_SIGNATURE,
             X509_ASN_ENCODING, (LPSTR)sigOID, 0, NULL, pubKeyInfo,
             &pubKeySize);
            ok(ret, "CryptExportKey failed: %08x\n", GetLastError());
            if (ret)
            {
                ret = CryptVerifyCertificateSignature(csp, X509_ASN_ENCODING,
                 cert, size, pubKeyInfo);
                ok(ret, "CryptVerifyCertificateSignature failed: %08x\n",
                 GetLastError());
            }
            HeapFree(GetProcessHeap(), 0, pubKeyInfo);
        }
        LocalFree(cert);
    }
}