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
typedef  int /*<<< orphan*/  md5_hmac ;
typedef  int /*<<< orphan*/  md5 ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  char* NTSTATUS ;
typedef  int /*<<< orphan*/ * BCRYPT_ALG_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  BCRYPT_ALG_HANDLE_HMAC_FLAG ; 
 int /*<<< orphan*/  BCRYPT_MD5_ALGORITHM ; 
 char* BCryptCloseAlgorithmProvider (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* BCryptOpenAlgorithmProvider (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_PRIMITIVE_PROVIDER ; 
 char* STATUS_SUCCESS ; 
 int /*<<< orphan*/  format_hash (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* pBCryptHash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  test_alg_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_hash_length (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_BcryptHash(void)
{
    static const char expected[] =
        "e2a3e68d23ce348b8f68b3079de3d4c9";
    static const char expected_hmac[] =
        "7bda029b93fa8d817fcc9e13d6bdf092";
    BCRYPT_ALG_HANDLE alg;
    UCHAR md5[16], md5_hmac[16];
    char str[65];
    NTSTATUS ret;

    alg = NULL;
    ret = BCryptOpenAlgorithmProvider(&alg, BCRYPT_MD5_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(alg != NULL, "alg not set\n");

    test_hash_length(alg, 16);
    test_alg_name(alg, "MD5");

    memset(md5, 0, sizeof(md5));
    ret = pBCryptHash(alg, NULL, 0, (UCHAR *)"test", sizeof("test"), md5, sizeof(md5));
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    format_hash( md5, sizeof(md5), str );
    ok(!strcmp(str, expected), "got %s\n", str);

    ret = BCryptCloseAlgorithmProvider(alg, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);

    alg = NULL;
    memset(md5_hmac, 0, sizeof(md5_hmac));
    ret = BCryptOpenAlgorithmProvider(&alg, BCRYPT_MD5_ALGORITHM, MS_PRIMITIVE_PROVIDER, BCRYPT_ALG_HANDLE_HMAC_FLAG);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    ok(alg != NULL, "alg not set\n");

    ret = pBCryptHash(alg, (UCHAR *)"key", sizeof("key"), (UCHAR *)"test", sizeof("test"), md5_hmac, sizeof(md5_hmac));
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
    format_hash( md5_hmac, sizeof(md5_hmac), str );
    ok(!strcmp(str, expected_hmac), "got %s\n", str);

    ret = BCryptCloseAlgorithmProvider(alg, 0);
    ok(ret == STATUS_SUCCESS, "got %08x\n", ret);
}