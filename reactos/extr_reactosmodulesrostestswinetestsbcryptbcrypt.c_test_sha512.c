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
typedef  int /*<<< orphan*/  sha512_hmac ;
typedef  int /*<<< orphan*/  sha512 ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  buf_hmac ;
typedef  int /*<<< orphan*/  buf ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  char* NTSTATUS ;
typedef  int /*<<< orphan*/ * BCRYPT_HASH_HANDLE ;
typedef  int /*<<< orphan*/ * BCRYPT_ALG_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  BCRYPT_ALG_HANDLE_HMAC_FLAG ; 
 int /*<<< orphan*/ * BCRYPT_OBJECT_LENGTH ; 
 int /*<<< orphan*/  BCRYPT_SHA512_ALGORITHM ; 
 char* BCryptCloseAlgorithmProvider (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* BCryptCreateHash (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* BCryptDestroyHash (int /*<<< orphan*/ *) ; 
 char* BCryptFinishHash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* BCryptGetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 char* BCryptHashData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* BCryptOpenAlgorithmProvider (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_PRIMITIVE_PROVIDER ; 
 char* STATUS_BUFFER_TOO_SMALL ; 
 char* STATUS_INVALID_HANDLE ; 
 char* STATUS_INVALID_PARAMETER ; 
 char* STATUS_SUCCESS ; 
 int /*<<< orphan*/  format_hash (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  test_alg_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_hash_length (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_sha512(void)
{
    static const char expected[] =
        "d55ced17163bf5386f2cd9ff21d6fd7fe576a915065c24744d09cfae4ec84ee1e"
        "f6ef11bfbc5acce3639bab725b50a1fe2c204f8c820d6d7db0df0ecbc49c5ca";
    static const char expected_hmac[] =
        "415fb6b10018ca03b38a1b1399c42ac0be5e8aceddb9a73103f5e543bf2d888f2"
        "eecf91373941f9315dd730a77937fa92444450fbece86f409d9cb5ec48c6513";
    BCRYPT_ALG_HANDLE alg;
    BCRYPT_HASH_HANDLE hash;
    UCHAR buf[512], buf_hmac[1024], sha512[64], sha512_hmac[64];
    ULONG size, len;
    char str[129];
    NTSTATUS ret;

    alg = NULL;
    ret = BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA512_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(alg != NULL, "alg not set\n");

    len = size = 0xdeadbeef;
    ret = BCryptGetProperty(NULL, BCRYPT_OBJECT_LENGTH, (UCHAR *)&len, sizeof(len), &size, 0);
    ok(ret == STATUS_INVALID_HANDLE, "got %08x\n", ret);

    len = size = 0xdeadbeef;
    ret = BCryptGetProperty(alg, NULL, (UCHAR *)&len, sizeof(len), &size, 0);
    ok(ret == STATUS_INVALID_PARAMETER, "got %08x\n", ret);

    len = size = 0xdeadbeef;
    ret = BCryptGetProperty(alg, BCRYPT_OBJECT_LENGTH, (UCHAR *)&len, sizeof(len), NULL, 0);
    ok(ret == STATUS_INVALID_PARAMETER, "got %08x\n", ret);

    len = size = 0xdeadbeef;
    ret = BCryptGetProperty(alg, BCRYPT_OBJECT_LENGTH, NULL, sizeof(len), &size, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(size == sizeof(len), "got %u\n", size);

    len = size = 0xdeadbeef;
    ret = BCryptGetProperty(alg, BCRYPT_OBJECT_LENGTH, (UCHAR *)&len, 0, &size, 0);
    ok(ret == STATUS_BUFFER_TOO_SMALL, "got %08x\n", ret);
    ok(len == 0xdeadbeef, "got %u\n", len);
    ok(size == sizeof(len), "got %u\n", size);

    len = size = 0xdeadbeef;
    ret = BCryptGetProperty(alg, BCRYPT_OBJECT_LENGTH, (UCHAR *)&len , sizeof(len), &size, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(len != 0xdeadbeef, "len not set\n");
    ok(size == sizeof(len), "got %u\n", size);

    test_hash_length(alg, 64);
    test_alg_name(alg, "SHA512");

    hash = NULL;
    len = sizeof(buf);
    ret = BCryptCreateHash(alg, &hash, buf, len, NULL, 0, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(hash != NULL, "hash not set\n");

    ret = BCryptHashData(hash, NULL, 0, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    ret = BCryptHashData(hash, (UCHAR *)"test", sizeof("test"), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    test_hash_length(hash, 64);
    test_alg_name(hash, "SHA512");

    memset(sha512, 0, sizeof(sha512));
    ret = BCryptFinishHash(hash, sha512, sizeof(sha512), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    format_hash( sha512, sizeof(sha512), str );
    ok(!strcmp(str, expected), "got %s\n", str);

    ret = BCryptDestroyHash(hash);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    ret = BCryptCloseAlgorithmProvider(alg, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    alg = NULL;
    ret = BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA512_ALGORITHM, MS_PRIMITIVE_PROVIDER, BCRYPT_ALG_HANDLE_HMAC_FLAG);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(alg != NULL, "alg not set\n");

    hash = NULL;
    len = sizeof(buf_hmac);
    ret = BCryptCreateHash(alg, &hash, buf_hmac, len, (UCHAR *)"key", sizeof("key"), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(hash != NULL, "hash not set\n");

    ret = BCryptHashData(hash, (UCHAR *)"test", sizeof("test"), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    test_hash_length(hash, 64);
    test_alg_name(hash, "SHA512");

    memset(sha512_hmac, 0, sizeof(sha512_hmac));
    ret = BCryptFinishHash(hash, sha512_hmac, sizeof(sha512_hmac), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    format_hash( sha512_hmac, sizeof(sha512_hmac), str );
    ok(!strcmp(str, expected_hmac), "got %s\n", str);

    ret = BCryptDestroyHash(hash);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    ret = BCryptCloseAlgorithmProvider(alg, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

}