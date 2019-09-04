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
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;
struct TYPE_3__ {char const* x500; size_t encodedSize; int /*<<< orphan*/  encoded; } ;
typedef  char* LPCWSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ CRYPT_E_INVALID_X500_STRING ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 char const* badlyQuotedCN_W ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* namesW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCertStrToNameW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,char**) ; 
 char const* simpleCN_W ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_CertStrToNameW(void)
{
    static const WCHAR bogusW[] = { 'b','o','g','u','s',0 };
    static const WCHAR fooW[] = { 'f','o','o','=','1',0 };
    BOOL ret;
    DWORD size, i;
    LPCWSTR errorPtr;
    BYTE buf[100];

    if (!pCertStrToNameW)
    {
        win_skip("CertStrToNameW is not available\n");
        return;
    }

    /* Crash
    ret = pCertStrToNameW(0, NULL, 0, NULL, NULL, NULL, NULL);
     */
    ret = pCertStrToNameW(0, NULL, 0, NULL, NULL, &size, NULL);
    ok(!ret, "Expected failure\n");
    ret = pCertStrToNameW(0, bogusW, 0, NULL, NULL, &size, NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
     "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameW(0, fooW, 0, NULL, NULL, &size, NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
     "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameW(0, simpleCN_W, 0, NULL, NULL, &size, NULL);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    ret = pCertStrToNameW(X509_ASN_ENCODING, simpleCN_W, 0, NULL, NULL, &size,
     NULL);
    ok(ret, "CertStrToNameW failed: %08x\n", GetLastError());
    size = sizeof(buf);
    ret = pCertStrToNameW(X509_ASN_ENCODING, badlyQuotedCN_W, 0, NULL, buf,
     &size, NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
     "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameW(X509_ASN_ENCODING, badlyQuotedCN_W, 0, NULL, buf,
     &size, &errorPtr);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
     "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ok(errorPtr && *errorPtr == '1', "Expected first error character was 1\n");
    for (i = 0; i < ARRAY_SIZE(namesW); i++)
    {
        size = sizeof(buf);
        ret = pCertStrToNameW(X509_ASN_ENCODING, namesW[i].x500, 0, NULL, buf,
         &size, NULL);
        ok(ret, "Index %d: CertStrToNameW failed: %08x\n", i, GetLastError());
        ok(size == namesW[i].encodedSize,
         "Index %d: expected size %d, got %d\n", i, namesW[i].encodedSize,
         size);
        if (ret)
            ok(!memcmp(buf, namesW[i].encoded, size),
             "Index %d: unexpected value for string %s\n", i, wine_dbgstr_w(namesW[i].x500));
    }
}