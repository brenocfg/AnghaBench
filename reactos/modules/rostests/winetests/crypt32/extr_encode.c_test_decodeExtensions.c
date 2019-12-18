#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ cExtension; TYPE_4__* rgExtension; } ;
struct TYPE_15__ {scalar_t__* encoded; TYPE_5__ exts; } ;
struct TYPE_14__ {scalar_t__ cExtension; TYPE_2__* rgExtension; } ;
struct TYPE_11__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_12__ {TYPE_3__ Value; int /*<<< orphan*/  pszObjId; } ;
struct TYPE_9__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_10__ {TYPE_1__ Value; int /*<<< orphan*/  pszObjId; } ;
typedef  size_t DWORD ;
typedef  TYPE_6__ CERT_EXTENSIONS ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_7__*) ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_EXTENSIONS ; 
 TYPE_7__* exts ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCryptDecodeObjectEx (size_t,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_decodeExtensions(DWORD dwEncoding)
{
    DWORD i;

    for (i = 0; i < ARRAY_SIZE(exts); i++)
    {
        BOOL ret;
        BYTE *buf = NULL;
        DWORD bufSize = 0;

        ret = pCryptDecodeObjectEx(dwEncoding, X509_EXTENSIONS,
         exts[i].encoded, exts[i].encoded[1] + 2, CRYPT_DECODE_ALLOC_FLAG,
         NULL, &buf, &bufSize);
        ok(ret, "CryptDecodeObjectEx failed: %08x\n", GetLastError());
        if (ret)
        {
            CERT_EXTENSIONS *ext = (CERT_EXTENSIONS *)buf;
            DWORD j;

            ok(ext->cExtension == exts[i].exts.cExtension,
             "Expected %d extensions, see %d\n", exts[i].exts.cExtension,
             ext->cExtension);
            for (j = 0; j < min(ext->cExtension, exts[i].exts.cExtension); j++)
            {
                ok(!strcmp(ext->rgExtension[j].pszObjId,
                 exts[i].exts.rgExtension[j].pszObjId),
                 "Expected OID %s, got %s\n",
                 exts[i].exts.rgExtension[j].pszObjId,
                 ext->rgExtension[j].pszObjId);
                ok(!memcmp(ext->rgExtension[j].Value.pbData,
                 exts[i].exts.rgExtension[j].Value.pbData,
                 exts[i].exts.rgExtension[j].Value.cbData),
                 "Unexpected value\n");
            }
            LocalFree(buf);
        }
        ret = pCryptDecodeObjectEx(dwEncoding, X509_EXTENSIONS,
         exts[i].encoded, exts[i].encoded[1] + 2, 0, NULL, NULL, &bufSize);
        ok(ret, "CryptDecodeObjectEx failed: %08x\n", GetLastError());
        buf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, bufSize);
        if (buf)
        {
            ret = pCryptDecodeObjectEx(dwEncoding, X509_EXTENSIONS,
             exts[i].encoded, exts[i].encoded[1] + 2, 0, NULL, buf, &bufSize);
            ok(ret, "CryptDecodeObjectEx failed: %08x\n", GetLastError());
            HeapFree(GetProcessHeap(), 0, buf);
        }
    }
}