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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MUI_LANGUAGE_ID ; 
 int MUI_UI_FALLBACK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetThreadPreferredUILanguages (int,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetThreadPreferredUILanguages(void)
{
    BOOL ret;
    ULONG count, size;
    WCHAR *buf;

    if (!pGetThreadPreferredUILanguages)
    {
        win_skip("GetThreadPreferredUILanguages is not available.\n");
        return;
    }

    size = count = 0;
    ret = pGetThreadPreferredUILanguages(MUI_LANGUAGE_ID|MUI_UI_FALLBACK, &count, NULL, &size);
    ok(ret, "got %u\n", GetLastError());
    ok(count, "expected count > 0\n");
    ok(size, "expected size > 0\n");

    count = 0;
    buf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size * sizeof(WCHAR));
    ret = pGetThreadPreferredUILanguages(MUI_LANGUAGE_ID|MUI_UI_FALLBACK, &count, buf, &size);
    ok(ret, "got %u\n", GetLastError());
    ok(count, "expected count > 0\n");
    HeapFree(GetProcessHeap(), 0, buf);
}