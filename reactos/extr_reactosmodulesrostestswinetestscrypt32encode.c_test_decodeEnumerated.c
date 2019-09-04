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
struct TYPE_5__ {int val; scalar_t__* encoded; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 TYPE_1__* enumeratedTypes ; 
 TYPE_1__* enums ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pCryptDecodeObjectEx (size_t,TYPE_1__,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,size_t*) ; 

__attribute__((used)) static void test_decodeEnumerated(DWORD dwEncoding)
{
    DWORD i, j;

    for (i = 0; i < ARRAY_SIZE(enumeratedTypes); i++)
    {
        for (j = 0; j < ARRAY_SIZE(enums); j++)
        {
            BOOL ret;
            DWORD bufSize = sizeof(int);
            int val;

            ret = pCryptDecodeObjectEx(dwEncoding, enumeratedTypes[i],
             enums[j].encoded, enums[j].encoded[1] + 2, 0, NULL,
             &val, &bufSize);
            ok(ret, "CryptDecodeObjectEx failed: %08x\n", GetLastError());
            ok(bufSize == sizeof(int),
             "Got unexpected size %d for enumerated\n", bufSize);
            ok(val == enums[j].val, "Unexpected value %d, expected %d\n",
             val, enums[j].val);
        }
    }
}