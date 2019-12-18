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
typedef  int /*<<< orphan*/  expected3 ;
typedef  int /*<<< orphan*/  expected2 ;
typedef  int /*<<< orphan*/  expected ;
typedef  scalar_t__ HRESULT ;
typedef  int BYTE ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pHashData (int*,int,int*,int) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static void test_HashData(void)
{
    HRESULT res;
    BYTE input[16] = {0x51, 0x33, 0x4F, 0xA7, 0x45, 0x15, 0xF0, 0x52, 0x90,
                      0x2B, 0xE7, 0xF5, 0xFD, 0xE1, 0xA6, 0xA7};
    BYTE output[32];
    static const BYTE expected[] = {0x54, 0x9C, 0x92, 0x55, 0xCD, 0x82, 0xFF,
                                    0xA1, 0x8E, 0x0F, 0xCF, 0x93, 0x14, 0xAA,
                                    0xE3, 0x2D};
    static const BYTE expected2[] = {0x54, 0x9C, 0x92, 0x55, 0xCD, 0x82, 0xFF,
                                     0xA1, 0x8E, 0x0F, 0xCF, 0x93, 0x14, 0xAA,
                                     0xE3, 0x2D, 0x47, 0xFC, 0x80, 0xB8, 0xD0,
                                     0x49, 0xE6, 0x13, 0x2A, 0x30, 0x51, 0x8D,
                                     0xF9, 0x4B, 0x07, 0xA6};
    static const BYTE expected3[] = {0x2B, 0xDC, 0x9A, 0x1B, 0xF0, 0x5A, 0xF9,
                                     0xC6, 0xBE, 0x94, 0x6D, 0xF3, 0x33, 0xC1,
                                     0x36, 0x07};
    int i;

    /* Test hashing with identically sized input/output buffers. */
    res = pHashData(input, 16, output, 16);
    ok(res == S_OK, "Expected HashData to return S_OK, got 0x%08x\n", res);
    if(res == S_OK)
       ok(!memcmp(output, expected, sizeof(expected)),
          "Output buffer did not match expected contents\n");

    /* Test hashing with larger output buffer. */
    res = pHashData(input, 16, output, 32);
    ok(res == S_OK, "Expected HashData to return S_OK, got 0x%08x\n", res);
    if(res == S_OK)
       ok(!memcmp(output, expected2, sizeof(expected2)),
          "Output buffer did not match expected contents\n");

    /* Test hashing with smaller input buffer. */
    res = pHashData(input, 8, output, 16);
    ok(res == S_OK, "Expected HashData to return S_OK, got 0x%08x\n", res);
    if(res == S_OK)
       ok(!memcmp(output, expected3, sizeof(expected3)),
          "Output buffer did not match expected contents\n");

    /* Test passing NULL pointers for input/output parameters. */
    res = pHashData(NULL, 0, NULL, 0);
    ok(res == E_INVALIDARG || broken(res == S_OK), /* Windows 2000 */
       "Expected HashData to return E_INVALIDARG, got 0x%08x\n", res);

    res = pHashData(input, 0, NULL, 0);
    ok(res == E_INVALIDARG || broken(res == S_OK), /* Windows 2000 */
       "Expected HashData to return E_INVALIDARG, got 0x%08x\n", res);

    res = pHashData(NULL, 0, output, 0);
    ok(res == E_INVALIDARG || broken(res == S_OK), /* Windows 2000 */
       "Expected HashData to return E_INVALIDARG, got 0x%08x\n", res);

    /* Test passing valid pointers with sizes of zero. */
    for (i = 0; i < ARRAY_SIZE(input); i++)
        input[i] = 0x00;

    for (i = 0; i < ARRAY_SIZE(output); i++)
        output[i] = 0xFF;

    res = pHashData(input, 0, output, 0);
    ok(res == S_OK, "Expected HashData to return S_OK, got 0x%08x\n", res);

    /* The buffers should be unchanged. */
    for (i = 0; i < ARRAY_SIZE(input); i++)
    {
        ok(input[i] == 0x00, "Expected the input buffer to be unchanged\n");
        if(input[i] != 0x00) break;
    }

    for (i = 0; i < ARRAY_SIZE(output); i++)
    {
        ok(output[i] == 0xFF, "Expected the output buffer to be unchanged\n");
        if(output[i] != 0xFF) break;
    }

    /* Input/output parameters are not validated. */
    res = pHashData((BYTE *)0xdeadbeef, 0, (BYTE *)0xdeadbeef, 0);
    ok(res == S_OK, "Expected HashData to return S_OK, got 0x%08x\n", res);

    if (0)
    {
        res = pHashData((BYTE *)0xdeadbeef, 1, (BYTE *)0xdeadbeef, 1);
        trace("HashData returned 0x%08x\n", res);
    }
}