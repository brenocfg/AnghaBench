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
typedef  int /*<<< orphan*/ * LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/ * CryptMemAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptMemRealloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_cryptAllocate(void)
{
    LPVOID buf;

    buf = CryptMemAlloc(0);
    ok(buf != NULL, "CryptMemAlloc failed: %08x\n", GetLastError());
    CryptMemFree(buf);
    /* CryptMemRealloc(NULL, 0) fails pre-Vista */
    buf = CryptMemAlloc(0);
    buf = CryptMemRealloc(buf, 1);
    ok(buf != NULL, "CryptMemRealloc failed: %08x\n", GetLastError());
    CryptMemFree(buf);
}