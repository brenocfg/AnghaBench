#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__* encoded; } ;
struct TYPE_8__ {scalar_t__* encodedTime; } ;
struct TYPE_7__ {scalar_t__ cValue; TYPE_1__* rgValue; } ;
struct TYPE_6__ {scalar_t__ cbData; int /*<<< orphan*/  pbData; } ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CRYPT_SEQUENCE_OF_ANY ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_SEQUENCE_OF_ANY ; 
 scalar_t__* intSequence ; 
 TYPE_4__* ints ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 size_t min (scalar_t__,scalar_t__) ; 
 scalar_t__* mixedSequence ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCryptDecodeObjectEx (size_t,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 TYPE_3__* times ; 

__attribute__((used)) static void test_decodeSequenceOfAny(DWORD dwEncoding)
{
    BOOL ret;
    BYTE *buf = NULL;
    DWORD bufSize = 0;

    ret = pCryptDecodeObjectEx(dwEncoding, X509_SEQUENCE_OF_ANY, intSequence,
     intSequence[1] + 2, CRYPT_DECODE_ALLOC_FLAG, NULL, &buf, &bufSize);
    ok(ret, "CryptDecodeObjectEx failed: %08x\n", GetLastError());
    if (ret)
    {
        CRYPT_SEQUENCE_OF_ANY *seq = (CRYPT_SEQUENCE_OF_ANY *)buf;
        DWORD i;

        ok(seq->cValue == ARRAY_SIZE(ints), "Wrong elements %d\n", seq->cValue);
        for (i = 0; i < min(seq->cValue, ARRAY_SIZE(ints)); i++)
        {
            ok(seq->rgValue[i].cbData == ints[i].encoded[1] + 2,
             "Expected %d bytes, got %d\n", ints[i].encoded[1] + 2,
             seq->rgValue[i].cbData);
            ok(!memcmp(seq->rgValue[i].pbData, ints[i].encoded,
             ints[i].encoded[1] + 2), "Unexpected value\n");
        }
        LocalFree(buf);
    }
    ret = pCryptDecodeObjectEx(dwEncoding, X509_SEQUENCE_OF_ANY, mixedSequence,
     mixedSequence[1] + 2, CRYPT_DECODE_ALLOC_FLAG, NULL, &buf,
     &bufSize);
    ok(ret, "CryptDecodeObjectEx failed: %08x\n", GetLastError());
    if (ret)
    {
        CRYPT_SEQUENCE_OF_ANY *seq = (CRYPT_SEQUENCE_OF_ANY *)buf;

        ok(seq->cValue == ARRAY_SIZE(ints), "Wrong elements %d\n", seq->cValue);
        /* Just check the first element since it's all that changed */
        ok(seq->rgValue[0].cbData == times[0].encodedTime[1] + 2,
         "Expected %d bytes, got %d\n", times[0].encodedTime[1] + 2,
         seq->rgValue[0].cbData);
        ok(!memcmp(seq->rgValue[0].pbData, times[0].encodedTime,
         times[0].encodedTime[1] + 2), "Unexpected value\n");
        LocalFree(buf);
    }
}