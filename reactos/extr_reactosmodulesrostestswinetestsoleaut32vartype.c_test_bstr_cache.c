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
typedef  char WCHAR ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* CoTaskMemAlloc (int) ; 
 scalar_t__ GetEnvironmentVariableA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SysAllocString (char const*) ; 
 scalar_t__ SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SysFreeString (scalar_t__) ; 
 int SysStringLen (scalar_t__) ; 
 int /*<<< orphan*/  lstrcmpW (scalar_t__,char const*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_bstr_cache(void)
{
    BSTR str, str2, strs[20];
    unsigned i;

    static const WCHAR testW[] = {'t','e','s','t',0};

    if (GetEnvironmentVariableA("OANOCACHE", NULL, 0)) {
        skip("BSTR cache is disabled, some tests will be skipped.\n");
        return;
    }

    str = SysAllocString(testW);
    /* This should put the string into cache */
    SysFreeString(str);
    /* The string is in cache, this won't touch it */
    SysFreeString(str);

    ok(SysStringLen(str) == 4, "unexpected len\n");
    ok(!lstrcmpW(str, testW), "string changed\n");

    str2 = SysAllocString(testW);
    ok(str == str2, "str != str2\n");
    SysFreeString(str2);

    /* Fill the bucket with cached entries.
       We roll our own, to show that the cache doesn't use
       the bstr length field to determine bucket allocation. */
    for(i=0; i < ARRAY_SIZE(strs); i++)
    {
        DWORD_PTR *ptr = CoTaskMemAlloc(64);
        ptr[0] = 0;
        strs[i] = (BSTR)(ptr + 1);
    }
    for(i=0; i < ARRAY_SIZE(strs); i++)
        SysFreeString(strs[i]);

    /* Following allocation will be made from cache */
    str = SysAllocStringLen(NULL, 24);
    ok(str == strs[0], "str != strs[0]\n");

    /* Smaller buffers may also use larget cached buffers */
    str2 = SysAllocStringLen(NULL, 16);
    ok(str2 == strs[1], "str2 != strs[1]\n");

    SysFreeString(str);
    SysFreeString(str2);
    SysFreeString(str);
    SysFreeString(str2);
}