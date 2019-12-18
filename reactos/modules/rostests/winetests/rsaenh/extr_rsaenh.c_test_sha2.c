#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pbData ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_SHA_256 ; 
 int /*<<< orphan*/  CALG_SHA_384 ; 
 int /*<<< orphan*/  CALG_SHA_512 ; 
 int CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CryptDestroyHash (int /*<<< orphan*/ ) ; 
 int CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int CryptHashData (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HP_HASHSIZE ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 scalar_t__ NTE_BAD_ALGID ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_sha2(void)
{
    static const unsigned char sha256hash[32] = {
        0x10, 0xfc, 0x3c, 0x51, 0xa1, 0x52, 0xe9, 0x0e, 0x5b, 0x90,
        0x31, 0x9b, 0x60, 0x1d, 0x92, 0xcc, 0xf3, 0x72, 0x90, 0xef,
        0x53, 0xc3, 0x5f, 0xf9, 0x25, 0x07, 0x68, 0x7d, 0x8a, 0x91,
        0x1a, 0x08
    };
    static const unsigned char sha384hash[48] = {
        0x98, 0xd3, 0x3f, 0x89, 0x0b, 0x23, 0x33, 0x44, 0x61, 0x32,
        0x5a, 0x7c, 0xa3, 0x03, 0x89, 0xb5, 0x11, 0xd7, 0x41, 0xc8,
        0x54, 0x6b, 0x12, 0x0c, 0x40, 0x15, 0xb6, 0x2a, 0x03, 0x43,
        0xe5, 0x64, 0x7f, 0x10, 0x1e, 0xae, 0x47, 0xa9, 0x39, 0x05,
        0x6f, 0x40, 0x60, 0x94, 0xd6, 0xad, 0x80, 0x55
    };
    static const unsigned char sha512hash[64] = {
        0x37, 0x86, 0x0e, 0x7d, 0x25, 0xd9, 0xf9, 0x84, 0x3e, 0x3d,
        0xc7, 0x13, 0x95, 0x73, 0x42, 0x04, 0xfd, 0x13, 0xad, 0x23,
        0x39, 0x16, 0x32, 0x5f, 0x99, 0x3e, 0x3c, 0xee, 0x3f, 0x11,
        0x36, 0xf9, 0xc9, 0x66, 0x08, 0x70, 0xcc, 0x49, 0xd8, 0xe0,
        0x7d, 0xa1, 0x57, 0x62, 0x71, 0xa6, 0xc9, 0xa4, 0x24, 0x60,
        0xfc, 0xde, 0x9d, 0xb2, 0xf1, 0xd2, 0xc2, 0xfb, 0x2d, 0xbf,
        0xb7, 0xf4, 0x81, 0xd4
    };
    unsigned char pbData[2048];
    BOOL result;
    HCRYPTHASH hHash;
    BYTE pbHashValue[64];
    DWORD hashlen, len;
    int i;

    for (i=0; i<2048; i++) pbData[i] = (unsigned char)i;

    /* SHA-256 hash */
    SetLastError(0xdeadbeef);
    result = CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash);
    if (!result && GetLastError() == NTE_BAD_ALGID) {
        win_skip("SHA-256/384/512 hashes are not supported before Windows XP SP3\n");
        return;
    }
    ok(result, "%08x\n", GetLastError());
    if (result) {
        len = sizeof(DWORD);
        result = CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&hashlen, &len, 0);
        ok(result && (hashlen == 32), "%08x, hashlen: %d\n", GetLastError(), hashlen);

        result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
        ok(result, "%08x\n", GetLastError());

        len = 32;
        result = CryptGetHashParam(hHash, HP_HASHVAL, pbHashValue, &len, 0);
        ok(result, "%08x\n", GetLastError());

        ok(!memcmp(pbHashValue, sha256hash, 32), "Wrong SHA-256 hash!\n");

        result = CryptDestroyHash(hHash);
        ok(result, "%08x\n", GetLastError());
    }

    /* SHA-384 hash */
    result = CryptCreateHash(hProv, CALG_SHA_384, 0, 0, &hHash);
    ok(result, "%08x\n", GetLastError());
    if (result) {
        len = sizeof(DWORD);
        result = CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&hashlen, &len, 0);
        ok(result && (hashlen == 48), "%08x, hashlen: %d\n", GetLastError(), hashlen);

        result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
        ok(result, "%08x\n", GetLastError());

        len = 48;
        result = CryptGetHashParam(hHash, HP_HASHVAL, pbHashValue, &len, 0);
        ok(result, "%08x\n", GetLastError());

        ok(!memcmp(pbHashValue, sha384hash, 48), "Wrong SHA-384 hash!\n");

        result = CryptDestroyHash(hHash);
        ok(result, "%08x\n", GetLastError());
    }

    /* SHA-512 hash */
    result = CryptCreateHash(hProv, CALG_SHA_512, 0, 0, &hHash);
    ok(result, "%08x\n", GetLastError());
    if (result) {
        len = sizeof(DWORD);
        result = CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&hashlen, &len, 0);
        ok(result && (hashlen == 64), "%08x, hashlen: %d\n", GetLastError(), hashlen);

        result = CryptHashData(hHash, pbData, sizeof(pbData), 0);
        ok(result, "%08x\n", GetLastError());

        len = 64;
        result = CryptGetHashParam(hHash, HP_HASHVAL, pbHashValue, &len, 0);
        ok(result, "%08x\n", GetLastError());

        ok(!memcmp(pbHashValue, sha512hash, 64), "Wrong SHA-512 hash!\n");

        result = CryptDestroyHash(hHash);
        ok(result, "%08x\n", GetLastError());
    }
}