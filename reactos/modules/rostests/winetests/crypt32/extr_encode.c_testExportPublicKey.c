#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pszObjId; } ;
struct TYPE_7__ {TYPE_1__ Algorithm; } ;
typedef  TYPE_2__* PCERT_PUBLIC_KEY_INFO ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptExportPublicKeyInfoEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int CryptGenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NTE_NO_KEY ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szOID_RSA_RSA ; 

__attribute__((used)) static void testExportPublicKey(HCRYPTPROV csp, PCERT_PUBLIC_KEY_INFO *pInfo)
{
    BOOL ret;
    DWORD size = 0;
    HCRYPTKEY key;

    /* This crashes
    ret = CryptExportPublicKeyInfoEx(0, 0, 0, NULL, 0, NULL, NULL, NULL);
     */
    ret = CryptExportPublicKeyInfoEx(0, 0, 0, NULL, 0, NULL, NULL, &size);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "Expected ERROR_INVALID_PARAMETER, got %08x\n", GetLastError());
    ret = CryptExportPublicKeyInfoEx(0, AT_SIGNATURE, 0, NULL, 0, NULL, NULL,
     &size);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "Expected ERROR_INVALID_PARAMETER, got %08x\n", GetLastError());
    ret = CryptExportPublicKeyInfoEx(0, 0, X509_ASN_ENCODING, NULL, 0, NULL,
     NULL, &size);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "Expected ERROR_INVALID_PARAMETER, got %08x\n", GetLastError());
    ret = CryptExportPublicKeyInfoEx(0, AT_SIGNATURE, X509_ASN_ENCODING, NULL,
     0, NULL, NULL, &size);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "Expected ERROR_INVALID_PARAMETER, got %08x\n", GetLastError());
    /* Test with no key */
    ret = CryptExportPublicKeyInfoEx(csp, AT_SIGNATURE, X509_ASN_ENCODING, NULL,
     0, NULL, NULL, &size);
    ok(!ret && GetLastError() == NTE_NO_KEY, "Expected NTE_NO_KEY, got %08x\n",
     GetLastError());
    ret = CryptGenKey(csp, AT_SIGNATURE, 0, &key);
    ok(ret, "CryptGenKey failed: %08x\n", GetLastError());
    if (ret)
    {
        ret = CryptExportPublicKeyInfoEx(csp, AT_SIGNATURE, X509_ASN_ENCODING,
         NULL, 0, NULL, NULL, &size);
        ok(ret, "CryptExportPublicKeyInfoEx failed: %08x\n", GetLastError());
        *pInfo = HeapAlloc(GetProcessHeap(), 0, size);
        if (*pInfo)
        {
            ret = CryptExportPublicKeyInfoEx(csp, AT_SIGNATURE,
             X509_ASN_ENCODING, NULL, 0, NULL, *pInfo, &size);
            ok(ret, "CryptExportPublicKeyInfoEx failed: %08x\n",
             GetLastError());
            if (ret)
            {
                /* By default (we passed NULL as the OID) the OID is
                 * szOID_RSA_RSA.
                 */
                ok(!strcmp((*pInfo)->Algorithm.pszObjId, szOID_RSA_RSA),
                 "Expected %s, got %s\n", szOID_RSA_RSA,
                 (*pInfo)->Algorithm.pszObjId);
            }
        }
    }
    CryptDestroyKey(key);
}