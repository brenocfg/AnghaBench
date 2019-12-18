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
struct TYPE_3__ {size_t* encoded; int /*<<< orphan*/  exts; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CRYPT_ENCODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_EXTENSIONS ; 
 TYPE_1__* exts ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,size_t*,size_t) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCryptEncodeObjectEx (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static void test_encodeExtensions(DWORD dwEncoding)
{
    DWORD i;

    for (i = 0; i < ARRAY_SIZE(exts); i++)
    {
        BOOL ret;
        BYTE *buf = NULL;
        DWORD bufSize = 0;

        ret = pCryptEncodeObjectEx(dwEncoding, X509_EXTENSIONS, &exts[i].exts,
         CRYPT_ENCODE_ALLOC_FLAG, NULL, &buf, &bufSize);
        ok(ret, "CryptEncodeObjectEx failed: %08x\n", GetLastError());
        if (ret)
        {
            ok(bufSize == exts[i].encoded[1] + 2,
             "Expected %d bytes, got %d\n", exts[i].encoded[1] + 2, bufSize);
            ok(!memcmp(buf, exts[i].encoded, exts[i].encoded[1] + 2),
             "Unexpected value\n");
            LocalFree(buf);
        }
    }
}