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
typedef  int /*<<< orphan*/ * HSTRING_TABLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pStringTableAddString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pStringTableDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pStringTableInitialize () ; 
 int pStringTableLookUpString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pStringTableStringFromId (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * string ; 
 int wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_StringTableStringFromId(void)
{
    HSTRING_TABLE table;
    WCHAR *string2;
    DWORD id, id2;

    table = pStringTableInitialize();
    ok(table != NULL, "Failed to Initialize String Table\n");

    id = pStringTableAddString(table, string, 0);
    ok(id != -1, "failed to add 'string' to string table\n");

    /* correct */
    id2 = pStringTableLookUpString(table, string, 0);
    ok(id2 == id, "got %d and %d\n", id2, id);

    string2 = pStringTableStringFromId(table, id2);
    ok(string2 != NULL, "failed to lookup string %d\n", id2);
    ok(!lstrcmpiW(string, string2), "got %s, expected %s\n", wine_dbgstr_w(string2), wine_dbgstr_w(string));

    pStringTableDestroy(table);
}