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
typedef  int /*<<< orphan*/ * HSTRING_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pStringTableDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pStringTableDuplicate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pStringTableInitialize () ; 

__attribute__((used)) static void test_StringTableDuplicate(void)
{
    HSTRING_TABLE table, table2;

    table = pStringTableInitialize();
    ok(table != NULL,"Failed to Initialize String Table\n");

    table2=pStringTableDuplicate(table);
    ok(table2!=NULL,"Failed to duplicate String Table\n");

    pStringTableDestroy(table);
    pStringTableDestroy(table2);
}