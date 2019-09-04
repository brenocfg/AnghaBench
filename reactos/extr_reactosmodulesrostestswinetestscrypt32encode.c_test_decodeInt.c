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
typedef  int /*<<< orphan*/  longForm ;
typedef  int /*<<< orphan*/  extraBytes ;
struct TYPE_7__ {int* encoded; int /*<<< orphan*/ **** val; int /*<<< orphan*/ **** decoded; } ;
struct TYPE_6__ {int cbData; int* pbData; } ;
typedef  int DWORD ;
typedef  TYPE_1__ CRYPT_INTEGER_BLOB ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int CRYPT_E_ASN1_BADTAG ; 
 int CRYPT_E_ASN1_EOD ; 
 int CRYPT_E_ASN1_LARGE ; 
 int ERROR_FILE_NOT_FOUND ; 
 int GetLastError () ; 
 int /*<<< orphan*/  LocalFree (int*) ; 
 int NOERROR ; 
 int OSS_BAD_ARG ; 
 int OSS_PDU_MISMATCH ; 
 int STATUS_ACCESS_VIOLATION ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  X509_INTEGER ; 
 int /*<<< orphan*/  X509_MULTI_BYTE_INTEGER ; 
 int /*<<< orphan*/  X509_MULTI_BYTE_UINT ; 
 TYPE_2__* bigInts ; 
 TYPE_2__* bigUInts ; 
 scalar_t__ broken (int) ; 
 TYPE_2__* ints ; 
 int /*<<< orphan*/  lstrlenA (char const*) ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ***,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCryptDecodeObjectEx (int,int /*<<< orphan*/ ,int const*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int**,int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void test_decodeInt(DWORD dwEncoding)
{
    static const BYTE bigInt[] = { 2, 5, 0xff, 0xfe, 0xff, 0xfe, 0xff };
    static const BYTE testStr[] = { 0x16, 4, 't', 'e', 's', 't' };
    static const BYTE longForm[] = { 2, 0x81, 0x01, 0x01 };
    static const BYTE bigBogus[] = { 0x02, 0x84, 0x01, 0xff, 0xff, 0xf9 };
    static const BYTE extraBytes[] = { 2, 1, 1, 0, 0, 0, 0 };
    BYTE *buf = NULL;
    DWORD bufSize = 0;
    int i;
    BOOL ret;

    /* CryptDecodeObjectEx with NULL bufSize crashes..
    ret = pCryptDecodeObjectEx(3, X509_INTEGER, &ints[0].encoded,
     ints[0].encoded[1] + 2, 0, NULL, NULL, NULL);
     */
    /* check bogus encoding */
    ret = pCryptDecodeObjectEx(3, X509_INTEGER, (BYTE *)&ints[0].encoded,
     ints[0].encoded[1] + 2, 0, NULL, NULL, &bufSize);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());
    /* check with NULL integer buffer */
    ret = pCryptDecodeObjectEx(dwEncoding, X509_INTEGER, NULL, 0, 0, NULL, NULL,
     &bufSize);
    ok(!ret && (GetLastError() == CRYPT_E_ASN1_EOD ||
     GetLastError() == OSS_BAD_ARG /* Win9x */),
     "Expected CRYPT_E_ASN1_EOD or OSS_BAD_ARG, got %08x\n", GetLastError());
    /* check with a valid, but too large, integer */
    ret = pCryptDecodeObjectEx(dwEncoding, X509_INTEGER, bigInt, bigInt[1] + 2,
     CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
    ok((!ret && GetLastError() == CRYPT_E_ASN1_LARGE) ||
     broken(ret) /* Win9x */,
     "Expected CRYPT_E_ASN1_LARGE, got %d\n", GetLastError());
    /* check with a DER-encoded string */
    ret = pCryptDecodeObjectEx(dwEncoding, X509_INTEGER, testStr, testStr[1] + 2,
     CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
    ok(!ret && (GetLastError() == CRYPT_E_ASN1_BADTAG ||
     GetLastError() == OSS_PDU_MISMATCH /* Win9x */ ),
     "Expected CRYPT_E_ASN1_BADTAG or OSS_PDU_MISMATCH, got %08x\n",
     GetLastError());
    for (i = 0; i < ARRAY_SIZE(ints); i++)
    {
        /* When the output buffer is NULL, this always succeeds */
        SetLastError(0xdeadbeef);
        ret = pCryptDecodeObjectEx(dwEncoding, X509_INTEGER,
         ints[i].encoded, ints[i].encoded[1] + 2, 0, NULL, NULL,
         &bufSize);
        ok(ret && GetLastError() == NOERROR,
         "Expected success and NOERROR, got %d\n", GetLastError());
        ret = pCryptDecodeObjectEx(dwEncoding, X509_INTEGER,
         ints[i].encoded, ints[i].encoded[1] + 2,
         CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
        ok(ret, "CryptDecodeObjectEx failed: %d\n", GetLastError());
        ok(bufSize == sizeof(int), "Wrong size %d\n", bufSize);
        ok(buf != NULL, "Expected allocated buffer\n");
        if (ret)
        {
            ok(!memcmp(buf, &ints[i].val, bufSize), "Expected %d, got %d\n",
             ints[i].val, *(int *)buf);
            LocalFree(buf);
        }
    }
    for (i = 0; i < ARRAY_SIZE(bigInts); i++)
    {
        ret = pCryptDecodeObjectEx(dwEncoding, X509_MULTI_BYTE_INTEGER,
         bigInts[i].encoded, bigInts[i].encoded[1] + 2, 0, NULL, NULL,
         &bufSize);
        ok(ret && GetLastError() == NOERROR,
         "Expected success and NOERROR, got %d\n", GetLastError());
        ret = pCryptDecodeObjectEx(dwEncoding, X509_MULTI_BYTE_INTEGER,
         bigInts[i].encoded, bigInts[i].encoded[1] + 2,
         CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
        ok(ret, "CryptDecodeObjectEx failed: %d\n", GetLastError());
        ok(bufSize >= sizeof(CRYPT_INTEGER_BLOB), "Wrong size %d\n", bufSize);
        ok(buf != NULL, "Expected allocated buffer\n");
        if (ret)
        {
            CRYPT_INTEGER_BLOB *blob = (CRYPT_INTEGER_BLOB *)buf;

            ok(blob->cbData == strlen((const char*)bigInts[i].decoded),
             "Expected len %d, got %d\n", lstrlenA((const char*)bigInts[i].decoded),
             blob->cbData);
            ok(!memcmp(blob->pbData, bigInts[i].decoded, blob->cbData),
             "Unexpected value\n");
            LocalFree(buf);
        }
    }
    for (i = 0; i < ARRAY_SIZE(bigUInts); i++)
    {
        ret = pCryptDecodeObjectEx(dwEncoding, X509_MULTI_BYTE_UINT,
         bigUInts[i].encoded, bigUInts[i].encoded[1] + 2, 0, NULL, NULL,
         &bufSize);
        ok(ret && GetLastError() == NOERROR,
         "Expected success and NOERROR, got %d\n", GetLastError());
        ret = pCryptDecodeObjectEx(dwEncoding, X509_MULTI_BYTE_UINT,
         bigUInts[i].encoded, bigUInts[i].encoded[1] + 2,
         CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
        ok(ret, "CryptDecodeObjectEx failed: %d\n", GetLastError());
        ok(bufSize >= sizeof(CRYPT_INTEGER_BLOB), "Wrong size %d\n", bufSize);
        ok(buf != NULL, "Expected allocated buffer\n");
        if (ret)
        {
            CRYPT_INTEGER_BLOB *blob = (CRYPT_INTEGER_BLOB *)buf;

            ok(blob->cbData == strlen((const char*)bigUInts[i].val),
             "Expected len %d, got %d\n", lstrlenA((const char*)bigUInts[i].val),
             blob->cbData);
            ok(!memcmp(blob->pbData, bigUInts[i].val, blob->cbData),
             "Unexpected value\n");
            LocalFree(buf);
        }
    }
    /* Decode the value 1 with long-form length */
    ret = pCryptDecodeObjectEx(dwEncoding, X509_MULTI_BYTE_INTEGER, longForm,
     sizeof(longForm), CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
    ok(ret, "CryptDecodeObjectEx failed: %08x\n", GetLastError());
    if (ret)
    {
        ok(*(int *)buf == 1, "Expected 1, got %d\n", *(int *)buf);
        LocalFree(buf);
    }
    /* check with extra bytes at the end */
    ret = pCryptDecodeObjectEx(dwEncoding, X509_INTEGER, extraBytes,
     sizeof(extraBytes), CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
    ok(ret, "CryptDecodeObjectEx failed: %08x\n", GetLastError());
    if (ret)
    {
        ok(*(int *)buf == 1, "Expected 1, got %d\n", *(int *)buf);
        LocalFree(buf);
    }
    /* Try to decode some bogus large items */
    /* The buffer size is smaller than the encoded length, so this should fail
     * with CRYPT_E_ASN1_EOD if it's being decoded.
     * Under XP it fails with CRYPT_E_ASN1_LARGE, which means there's a limit
     * on the size decoded, but in ME it fails with CRYPT_E_ASN1_EOD or crashes.
     * So this test unfortunately isn't useful.
    ret = pCryptDecodeObjectEx(dwEncoding, X509_MULTI_BYTE_INTEGER, tooBig,
     0x7fffffff, CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
    ok(!ret && GetLastError() == CRYPT_E_ASN1_LARGE,
     "Expected CRYPT_E_ASN1_LARGE, got %08x\n", GetLastError());
     */
    /* This will try to decode the buffer and overflow it, check that it's
     * caught.
     */
    if (0)
    {
    /* a large buffer isn't guaranteed to crash, it depends on memory allocation order */
    ret = pCryptDecodeObjectEx(dwEncoding, X509_MULTI_BYTE_INTEGER, bigBogus,
     0x01ffffff, CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
    ok(!ret && GetLastError() == STATUS_ACCESS_VIOLATION,
     "Expected STATUS_ACCESS_VIOLATION, got %08x\n", GetLastError());
    }
}