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
typedef  int LONG ;
typedef  int /*<<< orphan*/  IHTMLTableRow ;
typedef  int /*<<< orphan*/  IHTMLTable ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int HRESULT ;

/* Variables and functions */
 int IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLTableRow_Release (int /*<<< orphan*/ *) ; 
 int IHTMLTableRow_get_rowIndex (int /*<<< orphan*/ *,int*) ; 
 int IHTMLTable_deleteRow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IHTMLTable_insertRow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLTableRow ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_table_length (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_table_modify(IHTMLTable *table)
{
    IDispatch *disp;
    IHTMLTableRow *row;
    HRESULT hres;
    LONG index;

    test_table_length(table, 2);

    hres = IHTMLTable_insertRow(table, 0, &disp);
    ok(hres == S_OK, "insertRow failed: %08x\n", hres);
    ok(disp != NULL, "disp == NULL\n");
    test_table_length(table, 3);
    if (hres != S_OK || disp == NULL)
        return;

    hres = IDispatch_QueryInterface(disp, &IID_IHTMLTableRow, (void**)&row);
    IDispatch_Release(disp);

    ok(hres == S_OK, "QueryInterface failed: %08x\n", hres);
    ok(row != NULL, "row == NULL\n");

    index = 0xdeadbeef;
    hres = IHTMLTableRow_get_rowIndex(row, &index);
    ok(hres == S_OK, "get_rowIndex failed: %08x\n", hres);
    ok(index == 0, "index = %d, expected 0\n", index);

    IHTMLTableRow_Release(row);

    hres = IHTMLTable_deleteRow(table, 0);
    ok(hres == S_OK, "deleteRow failed: %08x\n", hres);
    test_table_length(table, 2);
}