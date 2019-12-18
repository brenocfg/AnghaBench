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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ST_CASE_SENSITIVE_COMPARE ; 
 int /*<<< orphan*/  String ; 
 int /*<<< orphan*/  foo ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pStringTableAddStringEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pStringTableDestroy (int /*<<< orphan*/ *) ; 
 int pStringTableGetExtraData (int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/ * pStringTableInitialize () ; 
 int /*<<< orphan*/ * pStringTableInitializeEx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string ; 

__attribute__((used)) static void test_StringTableAddStringEx(void)
{
    DWORD retval, hstring, hString, hfoo, extra;
    HANDLE table;
    BOOL ret;

    table = pStringTableInitialize();
    ok(table != NULL,"Failed to Initialize String Table\n");

    /* case insensitive */
    hstring = pStringTableAddStringEx(table, string, 0, NULL, 0);
    ok(hstring != -1, "Failed to add string to String Table\n");

    retval = pStringTableAddStringEx(table, String, 0, NULL, 0);
    ok(retval != -1, "Failed to add String to String Table\n");
    ok(hstring == retval, "string handle %x != String handle %x in String Table\n", hstring, retval);

    hfoo = pStringTableAddStringEx(table, foo, 0, NULL, 0);
    ok(hfoo != -1, "Failed to add foo to String Table\n");
    ok(hfoo != hstring, "foo and string share the same ID %x in String Table\n", hfoo);

    /* case sensitive */
    hString = pStringTableAddStringEx(table, String, ST_CASE_SENSITIVE_COMPARE, NULL, 0);
    ok(hstring != hString, "String handle and string share same ID %x in Table\n", hstring);

    pStringTableDestroy(table);

    /* set same string twice but with different extra */
    table = pStringTableInitializeEx(4, 0);
    ok(table != NULL, "Failed to Initialize String Table\n");

    extra = 10;
    hstring = pStringTableAddStringEx(table, string, 0, &extra, 4);
    ok(hstring != -1, "failed to add string, %d\n", hstring);

    extra = 0;
    ret = pStringTableGetExtraData(table, hstring, &extra, 4);
    ok(ret && extra == 10, "got %d, extra %d\n", ret, extra);

    extra = 11;
    hstring = pStringTableAddStringEx(table, string, 0, &extra, 4);
    ok(hstring != -1, "failed to add string, %d\n", hstring);

    extra = 0;
    ret = pStringTableGetExtraData(table, hstring, &extra, 4);
    ok(ret && extra == 10, "got %d, extra %d\n", ret, extra);

    pStringTableDestroy(table);
}