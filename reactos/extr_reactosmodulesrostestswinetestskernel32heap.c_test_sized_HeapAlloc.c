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
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_sized_HeapAlloc(int nbytes)
{
    BOOL success;
    char *buf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, nbytes);
    ok(buf != NULL, "allocate failed\n");
    ok(buf[0] == 0, "buffer not zeroed\n");
    success = HeapFree(GetProcessHeap(), 0, buf);
    ok(success, "free failed\n");
}