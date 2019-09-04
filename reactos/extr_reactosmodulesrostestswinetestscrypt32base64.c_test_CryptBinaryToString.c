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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int toEncodeLen; int /*<<< orphan*/ * toEncode; int /*<<< orphan*/  base64; } ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/ * CERT_HEADER ; 
 int /*<<< orphan*/ * CERT_HEADER_NOCR ; 
 int /*<<< orphan*/ * CERT_REQUEST_HEADER ; 
 int /*<<< orphan*/ * CERT_REQUEST_HEADER_NOCR ; 
 int /*<<< orphan*/ * CERT_REQUEST_TRAILER ; 
 int /*<<< orphan*/ * CERT_REQUEST_TRAILER_NOCR ; 
 int /*<<< orphan*/ * CERT_TRAILER ; 
 int /*<<< orphan*/ * CERT_TRAILER_NOCR ; 
 int CRYPT_STRING_BASE64 ; 
 int CRYPT_STRING_BASE64HEADER ; 
 int CRYPT_STRING_BASE64REQUESTHEADER ; 
 int CRYPT_STRING_BASE64X509CRLHEADER ; 
 int CRYPT_STRING_BINARY ; 
 int CRYPT_STRING_NOCR ; 
 scalar_t__ CryptBinaryToStringA (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ CryptBinaryToStringW (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * X509_HEADER ; 
 int /*<<< orphan*/ * X509_HEADER_NOCR ; 
 int /*<<< orphan*/ * X509_TRAILER ; 
 int /*<<< orphan*/ * X509_TRAILER_NOCR ; 
 int /*<<< orphan*/  encodeAndCompareBase64_A (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_compare_base64_W (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * strdupAtoW (int /*<<< orphan*/ ) ; 
 TYPE_1__* tests ; 
 TYPE_1__* testsNoCR ; 

__attribute__((used)) static void test_CryptBinaryToString(void)
{
    DWORD strLen, strLen2, i;
    BOOL ret;

    ret = CryptBinaryToStringA(NULL, 0, 0, NULL, NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    strLen = 123;
    ret = CryptBinaryToStringA(NULL, 0, 0, NULL, &strLen);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    ok(strLen == 123, "Unexpected length.\n");

    if (0)
        ret = CryptBinaryToStringW(NULL, 0, 0, NULL, NULL);

    strLen = 123;
    ret = CryptBinaryToStringW(NULL, 0, 0, NULL, &strLen);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER, "Unexpected error %d\n", GetLastError());
    ok(strLen == 123, "Unexpected length.\n");

    for (i = 0; i < ARRAY_SIZE(tests); i++)
    {
        WCHAR *strW, *encodedW;
        LPSTR str = NULL;
        BOOL ret;

        strLen = 0;
        ret = CryptBinaryToStringA(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BINARY, NULL, &strLen);
        ok(ret, "CryptBinaryToStringA failed: %d\n", GetLastError());
        ok(strLen == tests[i].toEncodeLen, "Unexpected required length %u.\n", strLen);

        strLen2 = strLen;
        str = heap_alloc(strLen);
        ret = CryptBinaryToStringA(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BINARY, str, &strLen2);
        ok(ret, "CryptBinaryToStringA failed: %d\n", GetLastError());
        ok(strLen == strLen2, "Expected length %u, got %u\n", strLen, strLen2);
        ok(!memcmp(str, tests[i].toEncode, tests[i].toEncodeLen), "Unexpected value\n");
        heap_free(str);

        strLen = 0;
        ret = CryptBinaryToStringW(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BINARY, NULL, &strLen);
        ok(ret, "CryptBinaryToStringW failed: %d\n", GetLastError());
        ok(strLen == tests[i].toEncodeLen, "Unexpected required length %u.\n", strLen);

        strLen2 = strLen;
        strW = heap_alloc(strLen);
        ret = CryptBinaryToStringW(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BINARY, strW, &strLen2);
        ok(ret, "CryptBinaryToStringW failed: %d\n", GetLastError());
        ok(strLen == strLen2, "Expected length %u, got %u\n", strLen, strLen2);
        ok(!memcmp(strW, tests[i].toEncode, tests[i].toEncodeLen), "Unexpected value\n");
        heap_free(strW);

        encodeAndCompareBase64_A(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BASE64,
            tests[i].base64, NULL, NULL);
        encodeAndCompareBase64_A(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BASE64HEADER,
            tests[i].base64, CERT_HEADER, CERT_TRAILER);
        encodeAndCompareBase64_A(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BASE64REQUESTHEADER,
            tests[i].base64, CERT_REQUEST_HEADER, CERT_REQUEST_TRAILER);
        encodeAndCompareBase64_A(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BASE64X509CRLHEADER,
            tests[i].base64, X509_HEADER, X509_TRAILER);

        encodedW = strdupAtoW(tests[i].base64);

        encode_compare_base64_W(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BASE64, encodedW, NULL, NULL);
        encode_compare_base64_W(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BASE64HEADER, encodedW,
            CERT_HEADER, CERT_TRAILER);
        encode_compare_base64_W(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BASE64REQUESTHEADER,
            encodedW, CERT_REQUEST_HEADER, CERT_REQUEST_TRAILER);
        encode_compare_base64_W(tests[i].toEncode, tests[i].toEncodeLen, CRYPT_STRING_BASE64X509CRLHEADER, encodedW,
            X509_HEADER, X509_TRAILER);

        heap_free(encodedW);
    }

    for (i = 0; i < ARRAY_SIZE(testsNoCR); i++)
    {
        LPSTR str = NULL;
        WCHAR *encodedW;
        BOOL ret;

        ret = CryptBinaryToStringA(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BINARY | CRYPT_STRING_NOCR, NULL, &strLen);
        ok(ret, "CryptBinaryToStringA failed: %d\n", GetLastError());

        strLen2 = strLen;
        str = heap_alloc(strLen);
        ret = CryptBinaryToStringA(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BINARY | CRYPT_STRING_NOCR, str, &strLen2);
        ok(ret, "CryptBinaryToStringA failed: %d\n", GetLastError());
        ok(strLen == strLen2, "Expected length %d, got %d\n", strLen, strLen2);
        ok(!memcmp(str, testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen), "Unexpected value\n");
        heap_free(str);

        encodeAndCompareBase64_A(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCR,
            testsNoCR[i].base64, NULL, NULL);
        encodeAndCompareBase64_A(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BASE64HEADER | CRYPT_STRING_NOCR, testsNoCR[i].base64, CERT_HEADER_NOCR, CERT_TRAILER_NOCR);
        encodeAndCompareBase64_A(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BASE64REQUESTHEADER | CRYPT_STRING_NOCR, testsNoCR[i].base64, CERT_REQUEST_HEADER_NOCR,
            CERT_REQUEST_TRAILER_NOCR);
        encodeAndCompareBase64_A(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BASE64X509CRLHEADER | CRYPT_STRING_NOCR, testsNoCR[i].base64, X509_HEADER_NOCR, X509_TRAILER_NOCR);

        encodedW = strdupAtoW(testsNoCR[i].base64);

        encode_compare_base64_W(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BASE64 | CRYPT_STRING_NOCR, encodedW, NULL, NULL);
        encode_compare_base64_W(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BASE64HEADER | CRYPT_STRING_NOCR, encodedW, CERT_HEADER_NOCR, CERT_TRAILER_NOCR);
        encode_compare_base64_W(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BASE64REQUESTHEADER | CRYPT_STRING_NOCR, encodedW, CERT_REQUEST_HEADER_NOCR,
            CERT_REQUEST_TRAILER_NOCR);
        encode_compare_base64_W(testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen,
            CRYPT_STRING_BASE64X509CRLHEADER | CRYPT_STRING_NOCR, encodedW,
            X509_HEADER_NOCR, X509_TRAILER_NOCR);

        heap_free(encodedW);
    }
}