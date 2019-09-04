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
struct TYPE_3__ {char* x500; size_t encodedSize; int /*<<< orphan*/  encoded; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CERT_NAME_STR_NO_PLUS_FLAG ; 
 int /*<<< orphan*/  CERT_NAME_STR_NO_QUOTING_FLAG ; 
 scalar_t__ CRYPT_E_INVALID_X500_STRING ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* namesA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCertStrToNameA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_CertStrToNameA(void)
{
    BOOL ret;
    DWORD size, i;
    BYTE buf[100];

    if (!pCertStrToNameA)
    {
        win_skip("CertStrToNameA is not available\n");
        return;
    }

    /* Crash
    ret = pCertStrToNameA(0, NULL, 0, NULL, NULL, NULL, NULL);
     */
    ret = pCertStrToNameA(0, NULL, 0, NULL, NULL, &size, NULL);
    ok(!ret, "Expected failure\n");
    ret = pCertStrToNameA(0, "bogus", 0, NULL, NULL, &size, NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
     "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameA(0, "foo=1", 0, NULL, NULL, &size, NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
     "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameA(0, "CN=1", 0, NULL, NULL, &size, NULL);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=1", 0, NULL, NULL, &size, NULL);
    ok(ret, "CertStrToNameA failed: %08x\n", GetLastError());
    size = sizeof(buf);
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=\"\"1\"\"", 0, NULL, buf, &size,
     NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
     "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=1+2", 0, NULL, buf,
     &size, NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
     "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=1+2", CERT_NAME_STR_NO_PLUS_FLAG, NULL, buf,
                          &size, NULL);
    ok(ret && GetLastError() == ERROR_SUCCESS,
                 "Expected ERROR_SUCCESS, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=1,2", CERT_NAME_STR_NO_QUOTING_FLAG, NULL, buf,
                          &size, NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
                 "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=\"1,2;3,4\"", CERT_NAME_STR_NO_QUOTING_FLAG, NULL, buf,
                          &size, NULL);
    ok(!ret && GetLastError() == CRYPT_E_INVALID_X500_STRING,
                 "Expected CRYPT_E_INVALID_X500_STRING, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=abc", 0, NULL, buf,
                          &size, NULL);
    ok(ret && GetLastError() == ERROR_SUCCESS,
                 "Expected ERROR_SUCCESS, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=abc", CERT_NAME_STR_NO_QUOTING_FLAG, NULL, buf,
                          &size, NULL);
    ok(ret && GetLastError() == ERROR_SUCCESS,
                 "Expected ERROR_SUCCESS, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=\"abc\"", 0, NULL, buf,
                          &size, NULL);
    ok(ret && GetLastError() == ERROR_SUCCESS,
                 "Expected ERROR_SUCCESS, got %08x\n", GetLastError());
    ret = pCertStrToNameA(X509_ASN_ENCODING, "CN=\"abc\"", CERT_NAME_STR_NO_QUOTING_FLAG, NULL, buf,
                          &size, NULL);
    ok(!ret && GetLastError() == ERROR_MORE_DATA,
                 "Expected ERROR_MORE_DATA, got %08x\n", GetLastError());
    for (i = 0; i < ARRAY_SIZE(namesA); i++)
    {
        size = sizeof(buf);
        ret = pCertStrToNameA(X509_ASN_ENCODING, namesA[i].x500, 0, NULL, buf,
         &size, NULL);
        ok(ret, "CertStrToNameA failed on string %s: %08x\n", namesA[i].x500,
         GetLastError());
        ok(size == namesA[i].encodedSize,
         "Expected size %d, got %d\n", namesA[i].encodedSize, size);
        if (ret)
            ok(!memcmp(buf, namesA[i].encoded, namesA[i].encodedSize),
             "Unexpected value for string %s\n", namesA[i].x500);
    }
}