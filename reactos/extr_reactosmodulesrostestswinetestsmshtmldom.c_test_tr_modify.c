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
typedef  int /*<<< orphan*/  IHTMLTableRow ;
typedef  int /*<<< orphan*/  IHTMLTableCell ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLTableCell_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLTableRow_deleteCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IHTMLTableRow_insertCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLTableCell ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_tr_possess (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void test_tr_modify(IHTMLElement *elem, IHTMLTableRow *row)
{
    HRESULT hres;
    IDispatch *disp;
    IHTMLTableCell *cell;

    hres = IHTMLTableRow_deleteCell(row, 0);
    ok(hres == S_OK, "deleteCell failed: %08x\n", hres);
    test_tr_possess(elem, row, 1, "td2");

    hres = IHTMLTableRow_insertCell(row, 0, &disp);
    ok(hres == S_OK, "insertCell failed: %08x\n", hres);
    ok(disp != NULL, "disp == NULL\n");
    hres = IDispatch_QueryInterface(disp, &IID_IHTMLTableCell, (void **)&cell);
    ok(hres == S_OK, "Could not get IID_IHTMLTableCell interface: %08x\n", hres);
    ok(cell != NULL, "cell == NULL\n");
    if (SUCCEEDED(hres))
        IHTMLTableCell_Release(cell);
    test_tr_possess(elem, row, 2, "td2");
    IDispatch_Release(disp);
}