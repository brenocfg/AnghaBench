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
typedef  int /*<<< orphan*/  sha384_hmac ;
typedef  int /*<<< orphan*/  sha384 ;
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
 int /*<<< orphan*/  BCRYPT_SHA384_ALGORITHM ; 
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

__attribute__((used)) static void test_sha384(void)
{
    static const char expected[] =
        "62b21e90c9022b101671ba1f808f8631a8149f0f12904055839a35c1ca78ae5363eed1e743a692d70e0504b0cfd12ef9";
    static const char expected_hmac[] =
        "4b3e6d6ff2da121790ab7e7b9247583e3a7eed2db5bd4dabc680303b1608f37dfdc836d96a704c03283bc05b4f6c5eb8";
    BCRYPT_ALG_HANDLE alg;
    BCRYPT_HASH_HANDLE hash;
    UCHAR buf[512], buf_hmac[1024], sha384[48], sha384_hmac[48];
    ULONG size, len;
    char str[97];
    NTSTATUS ret;

    alg = NULL;
    ret = BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA384_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
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

    test_hash_length(alg, 48);
    test_alg_name(alg, "SHA384");

    hash = NULL;
    len = sizeof(buf);
    ret = BCryptCreateHash(alg, &hash, buf, len, NULL, 0, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(hash != NULL, "hash not set\n");

    ret = BCryptHashData(hash, NULL, 0, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    ret = BCryptHashData(hash, (UCHAR *)"test", sizeof("test"), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    test_hash_length(hash, 48);
    test_alg_name(hash, "SHA384");

    memset(sha384, 0, sizeof(sha384));
    ret = BCryptFinishHash(hash, sha384, sizeof(sha384), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    format_hash( sha384, sizeof(sha384), str );
    ok(!strcmp(str, expected), "got %s\n", str);

    ret = BCryptDestroyHash(hash);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    ret = BCryptCloseAlgorithmProvider(alg, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    alg = NULL;
    ret = BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA384_ALGORITHM, MS_PRIMITIVE_PROVIDER, BCRYPT_ALG_HANDLE_HMAC_FLAG);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(alg != NULL, "alg not set\n");

    hash = NULL;
    len = sizeof(buf_hmac);
    ret = BCryptCreateHash(alg, &hash, buf_hmac, len, (UCHAR *)"key", sizeof("key"), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(hash != NULL, "hash not set\n");

    ret = BCryptHashData(hash, (UCHAR *)"test", sizeof("test"), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    test_hash_length(hash, 48);
    test_alg_name(hash, "SHA384");

    memset(sha384_hmac, 0, sizeof(sha384_hmac));
    ret = BCryptFinishHash(hash, sha384_hmac, sizeof(sha384_hmac), 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    format_hash( sha384_hmac, sizeof(sha384_hmac), str );
    ok(!strcmp(str, expected_hmac), "got %s\n", str);

    ret = BCryptDestroyHash(hash);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    ret = BCryptCloseAlgorithmProvider(alg, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
}