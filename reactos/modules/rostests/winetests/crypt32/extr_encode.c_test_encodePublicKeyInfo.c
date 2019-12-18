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
struct TYPE_3__ {size_t* encoded; int /*<<< orphan*/  info; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CRYPT_ENCODE_ALLOC_FLAG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ OSS_BAD_PTR ; 
 int /*<<< orphan*/  X509_PUBLIC_KEY_INFO ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,size_t*,size_t) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCryptEncodeObjectEx (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 TYPE_1__* pubKeys ; 

__attribute__((used)) static void test_encodePublicKeyInfo(DWORD dwEncoding)
{
    DWORD i;

    for (i = 0; i < ARRAY_SIZE(pubKeys); i++)
    {
        BOOL ret;
        BYTE *buf = NULL;
        DWORD bufSize = 0;

        ret = pCryptEncodeObjectEx(dwEncoding, X509_PUBLIC_KEY_INFO,
         &pubKeys[i].info, CRYPT_ENCODE_ALLOC_FLAG, NULL, &buf,
         &bufSize);
        ok(ret || GetLastError() == OSS_BAD_PTR /* Win9x */,
         "CryptEncodeObjectEx failed: %08x\n", GetLastError());
        if (ret)
        {
            ok(bufSize == pubKeys[i].encoded[1] + 2,
             "Expected %d bytes, got %d\n", pubKeys[i].encoded[1] + 2, bufSize);
            if (bufSize == pubKeys[i].encoded[1] + 2)
                ok(!memcmp(buf, pubKeys[i].encoded, pubKeys[i].encoded[1] + 2),
                 "Unexpected value\n");
            LocalFree(buf);
        }
    }
}