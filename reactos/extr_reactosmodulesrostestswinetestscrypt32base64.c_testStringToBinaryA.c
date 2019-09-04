#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* base64; char* str; int format; int /*<<< orphan*/  toEncodeLen; int /*<<< orphan*/  toEncode; } ;
typedef  size_t DWORD ;
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * ALT_CERT_HEADER ; 
 int /*<<< orphan*/ * ALT_CERT_TRAILER ; 
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/ * CERT_HEADER ; 
 int /*<<< orphan*/ * CERT_REQUEST_HEADER ; 
 int /*<<< orphan*/ * CERT_REQUEST_TRAILER ; 
 int /*<<< orphan*/ * CERT_TRAILER ; 
 int CRYPT_STRING_ANY ; 
 int CRYPT_STRING_BASE64 ; 
 int CRYPT_STRING_BASE64HEADER ; 
 int CRYPT_STRING_BASE64REQUESTHEADER ; 
 int CRYPT_STRING_BASE64X509CRLHEADER ; 
 int CRYPT_STRING_BASE64_ANY ; 
 int CRYPT_STRING_NOCR ; 
 int /*<<< orphan*/  CryptStringToBinaryA (char*,int,int,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * X509_HEADER ; 
 int /*<<< orphan*/ * X509_TRAILER ; 
 TYPE_1__* badStrings ; 
 int /*<<< orphan*/  decodeAndCompareBase64_A (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decodeBase64WithFmt (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decodeBase64WithLen (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decodeBase64WithLenBroken (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 
 TYPE_1__* tests ; 
 TYPE_1__* testsNoCR ; 

__attribute__((used)) static void testStringToBinaryA(void)
{
    BOOL ret;
    DWORD bufLen = 0, i;
    BYTE buf[8];

    ret = CryptStringToBinaryA(NULL, 0, 0, NULL, NULL, NULL, NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "Expected ERROR_INVALID_PARAMETER, got ret=%d le=%u\n", ret, GetLastError());
    ret = CryptStringToBinaryA(NULL, 0, 0, NULL, &bufLen, NULL, NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "Expected ERROR_INVALID_PARAMETER, got ret=%d le=%u\n", ret, GetLastError());
    /* Bogus format */
    ret = CryptStringToBinaryA(tests[0].base64, 0, 0, NULL, &bufLen, NULL,
     NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_DATA,
     "Expected ERROR_INVALID_DATA, got ret=%d le=%u\n", ret, GetLastError());
    /* Decoding doesn't expect the NOCR flag to be specified */
    ret = CryptStringToBinaryA(tests[0].base64, 1,
     CRYPT_STRING_BASE64 | CRYPT_STRING_NOCR, NULL, &bufLen, NULL, NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_DATA,
     "Expected ERROR_INVALID_DATA, got ret=%d le=%u\n", ret, GetLastError());
    /* Bad strings */
    for (i = 0; i < ARRAY_SIZE(badStrings); i++)
    {
        bufLen = 0;
        ret = CryptStringToBinaryA(badStrings[i].str, 0, badStrings[i].format,
         NULL, &bufLen, NULL, NULL);
        ok(!ret && GetLastError() == ERROR_INVALID_DATA,
           "%d: Expected ERROR_INVALID_DATA, got ret=%d le=%u\n", i, ret, GetLastError());
    }
    /* Weird base64 strings (invalid padding, extra white-space etc.) */
    decodeBase64WithLen("V=", 0, 0, ERROR_INVALID_DATA);
    decodeBase64WithLen("VV=", 0, 0, ERROR_INVALID_DATA);
    decodeBase64WithLen("V==", 0, 0, ERROR_INVALID_DATA);
    decodeBase64WithLen("V=", 2, 0, ERROR_INVALID_DATA);
    decodeBase64WithLen("VV=", 3, 0, ERROR_INVALID_DATA);
    decodeBase64WithLen("V==", 3, 0, ERROR_INVALID_DATA);
    decodeBase64WithLenBroken("V", 0, "T", 0);
    decodeBase64WithLenBroken("VV", 0, "U", 0);
    decodeBase64WithLenBroken("VVV", 0, "UU", 0);
    decodeBase64WithLen("V", 1, "T", 0);
    decodeBase64WithLen("VV", 2, "U", 0);
    decodeBase64WithLen("VVV", 3, "UU", 0);
    decodeBase64WithLen("V===", 0, "T", 0);
    decodeBase64WithLen("V========", 0, "T", 0);
    decodeBase64WithLen("V===", 4, "T", 0);
    decodeBase64WithLen("V\nVVV", 0, "UUU", 0);
    decodeBase64WithLen("VV\nVV", 0, "UUU", 0);
    decodeBase64WithLen("VVV\nV", 0, "UUU", 0);
    decodeBase64WithLen("V\nVVV", 5, "UUU", 0);
    decodeBase64WithLen("VV\nVV", 5, "UUU", 0);
    decodeBase64WithLen("VVV\nV", 5, "UUU", 0);
    decodeBase64WithLen("VV    VV", 0, "UUU", 0);
    decodeBase64WithLen("V===VVVV", 0, "T", 0);
    decodeBase64WithLen("VV==VVVV", 0, "U", 0);
    decodeBase64WithLen("VVV=VVVV", 0, "UU", 0);
    decodeBase64WithLen("VVVV=VVVV", 0, "UUU", 0);
    decodeBase64WithLen("V===VVVV", 8, "T", 0);
    decodeBase64WithLen("VV==VVVV", 8, "U", 0);
    decodeBase64WithLen("VVV=VVVV", 8, "UU", 0);
    decodeBase64WithLen("VVVV=VVVV", 8, "UUU", 0);

    decodeBase64WithFmt("-----BEGIN-----VVVV-----END-----", CRYPT_STRING_BASE64HEADER, 0, ERROR_INVALID_DATA);
    decodeBase64WithFmt("-----BEGIN-----VVVV-----END -----", CRYPT_STRING_BASE64HEADER, 0, ERROR_INVALID_DATA);
    decodeBase64WithFmt("-----BEGIN -----VVVV-----END-----", CRYPT_STRING_BASE64HEADER, 0, ERROR_INVALID_DATA);
    decodeBase64WithFmt("-----BEGIN -----VVVV-----END -----", CRYPT_STRING_BASE64HEADER, "UUU", 0);

    decodeBase64WithFmt("-----BEGIN -----V-----END -----", CRYPT_STRING_BASE64HEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN foo-----V-----END -----", CRYPT_STRING_BASE64HEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN foo-----V-----END foo-----", CRYPT_STRING_BASE64HEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN -----V-----END foo-----", CRYPT_STRING_BASE64HEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN -----V-----END -----", CRYPT_STRING_BASE64X509CRLHEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN foo-----V-----END -----", CRYPT_STRING_BASE64X509CRLHEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN foo-----V-----END foo-----", CRYPT_STRING_BASE64X509CRLHEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN -----V-----END foo-----", CRYPT_STRING_BASE64X509CRLHEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN -----V-----END -----", CRYPT_STRING_BASE64REQUESTHEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN foo-----V-----END -----", CRYPT_STRING_BASE64REQUESTHEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN foo-----V-----END foo-----", CRYPT_STRING_BASE64REQUESTHEADER, "T", 0);
    decodeBase64WithFmt("-----BEGIN -----V-----END foo-----", CRYPT_STRING_BASE64REQUESTHEADER, "T", 0);

    /* Too small buffer */
    buf[0] = 0;
    bufLen = 4;
    ret = CryptStringToBinaryA("VVVVVVVV", 8, CRYPT_STRING_BASE64, (BYTE*)buf, &bufLen, NULL, NULL);
    ok(!ret && bufLen == 4 && buf[0] == 0,
     "Expected ret 0, bufLen 4, buf[0] '\\0', got ret %d, bufLen %d, buf[0] '%c'\n",
     ret, bufLen, buf[0]);

    /* Good strings */
    for (i = 0; i < ARRAY_SIZE(tests); i++)
    {
        bufLen = 0;
        /* Bogus length--oddly enough, that succeeds, even though it's not
         * properly padded.
         */
        ret = CryptStringToBinaryA(tests[i].base64, 1, CRYPT_STRING_BASE64,
         NULL, &bufLen, NULL, NULL);
        ok(ret, "CryptStringToBinaryA failed: %d\n", GetLastError());
        /* Check with the precise format */
        decodeAndCompareBase64_A(tests[i].base64, NULL, NULL,
         CRYPT_STRING_BASE64, CRYPT_STRING_BASE64, tests[i].toEncode,
         tests[i].toEncodeLen);
        decodeAndCompareBase64_A(tests[i].base64, CERT_HEADER, CERT_TRAILER,
         CRYPT_STRING_BASE64HEADER, CRYPT_STRING_BASE64HEADER,
         tests[i].toEncode, tests[i].toEncodeLen);
        decodeAndCompareBase64_A(tests[i].base64, ALT_CERT_HEADER, ALT_CERT_TRAILER,
         CRYPT_STRING_BASE64HEADER, CRYPT_STRING_BASE64HEADER,
         tests[i].toEncode, tests[i].toEncodeLen);
        decodeAndCompareBase64_A(tests[i].base64, CERT_REQUEST_HEADER,
         CERT_REQUEST_TRAILER, CRYPT_STRING_BASE64REQUESTHEADER,
         CRYPT_STRING_BASE64REQUESTHEADER, tests[i].toEncode,
         tests[i].toEncodeLen);
        decodeAndCompareBase64_A(tests[i].base64, X509_HEADER, X509_TRAILER,
         CRYPT_STRING_BASE64X509CRLHEADER, CRYPT_STRING_BASE64X509CRLHEADER,
         tests[i].toEncode, tests[i].toEncodeLen);
        /* And check with the "any" formats */
        decodeAndCompareBase64_A(tests[i].base64, NULL, NULL,
         CRYPT_STRING_BASE64_ANY, CRYPT_STRING_BASE64, tests[i].toEncode,
         tests[i].toEncodeLen);
        /* Don't check with no header and the string_any format, that'll
         * always succeed.
         */
        decodeAndCompareBase64_A(tests[i].base64, CERT_HEADER, CERT_TRAILER,
         CRYPT_STRING_BASE64_ANY, CRYPT_STRING_BASE64HEADER, tests[i].toEncode,
         tests[i].toEncodeLen);
        decodeAndCompareBase64_A(tests[i].base64, CERT_HEADER, CERT_TRAILER,
         CRYPT_STRING_ANY, CRYPT_STRING_BASE64HEADER, tests[i].toEncode,
         tests[i].toEncodeLen);
        /* oddly, these seem to decode using the wrong format
        decodeAndCompareBase64_A(tests[i].base64, CERT_REQUEST_HEADER,
         CERT_REQUEST_TRAILER, CRYPT_STRING_BASE64_ANY,
         CRYPT_STRING_BASE64REQUESTHEADER, tests[i].toEncode,
         tests[i].toEncodeLen);
        decodeAndCompareBase64_A(tests[i].base64, CERT_REQUEST_HEADER,
         CERT_REQUEST_TRAILER, CRYPT_STRING_ANY,
         CRYPT_STRING_BASE64REQUESTHEADER, tests[i].toEncode,
         tests[i].toEncodeLen);
        decodeAndCompareBase64_A(tests[i].base64, X509_HEADER, X509_TRAILER,
         CRYPT_STRING_BASE64_ANY, CRYPT_STRING_BASE64X509CRLHEADER,
         tests[i].toEncode, tests[i].toEncodeLen);
        decodeAndCompareBase64_A(tests[i].base64, X509_HEADER, X509_TRAILER,
         CRYPT_STRING_ANY, CRYPT_STRING_BASE64X509CRLHEADER, tests[i].toEncode,
         tests[i].toEncodeLen);
         */
    }
    /* And again, with no CR--decoding handles this automatically */
    for (i = 0; i < ARRAY_SIZE(testsNoCR); i++)
    {
        bufLen = 0;
        /* Bogus length--oddly enough, that succeeds, even though it's not
         * properly padded.
         */
        ret = CryptStringToBinaryA(testsNoCR[i].base64, 1, CRYPT_STRING_BASE64,
         NULL, &bufLen, NULL, NULL);
        ok(ret, "CryptStringToBinaryA failed: %d\n", GetLastError());
        /* Check with the precise format */
        decodeAndCompareBase64_A(testsNoCR[i].base64, NULL, NULL,
         CRYPT_STRING_BASE64, CRYPT_STRING_BASE64, testsNoCR[i].toEncode,
         testsNoCR[i].toEncodeLen);
        decodeAndCompareBase64_A(testsNoCR[i].base64, CERT_HEADER, CERT_TRAILER,
         CRYPT_STRING_BASE64HEADER, CRYPT_STRING_BASE64HEADER,
         testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen);
        decodeAndCompareBase64_A(testsNoCR[i].base64, CERT_REQUEST_HEADER,
         CERT_REQUEST_TRAILER, CRYPT_STRING_BASE64REQUESTHEADER,
         CRYPT_STRING_BASE64REQUESTHEADER, testsNoCR[i].toEncode,
         testsNoCR[i].toEncodeLen);
        decodeAndCompareBase64_A(testsNoCR[i].base64, X509_HEADER, X509_TRAILER,
         CRYPT_STRING_BASE64X509CRLHEADER, CRYPT_STRING_BASE64X509CRLHEADER,
         testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen);
        /* And check with the "any" formats */
        decodeAndCompareBase64_A(testsNoCR[i].base64, NULL, NULL,
         CRYPT_STRING_BASE64_ANY, CRYPT_STRING_BASE64, testsNoCR[i].toEncode,
         testsNoCR[i].toEncodeLen);
        /* Don't check with no header and the string_any format, that'll
         * always succeed.
         */
        decodeAndCompareBase64_A(testsNoCR[i].base64, CERT_HEADER, CERT_TRAILER,
         CRYPT_STRING_BASE64_ANY, CRYPT_STRING_BASE64HEADER,
         testsNoCR[i].toEncode, testsNoCR[i].toEncodeLen);
        decodeAndCompareBase64_A(testsNoCR[i].base64, CERT_HEADER, CERT_TRAILER,
         CRYPT_STRING_ANY, CRYPT_STRING_BASE64HEADER, testsNoCR[i].toEncode,
         testsNoCR[i].toEncodeLen);
    }
}