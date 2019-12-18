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
typedef  int /*<<< orphan*/  var ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IOleCommandTarget ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 scalar_t__ IOleCommandTarget_Exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleCommandTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OLECMDEXECOPT_DODEFAULT ; 
 int /*<<< orphan*/  OLECMDID_ONUNLOAD ; 
 scalar_t__ S_OK ; 
 scalar_t__ VARIANT_TRUE ; 
 scalar_t__ VT_BOOL ; 
 scalar_t__ V_BOOL (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_exec_onunload(IHTMLDocument2 *doc)
{
    IOleCommandTarget *cmdtrg;
    VARIANT var;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleCommandTarget, (void**)&cmdtrg);
    ok(hres == S_OK, "QueryInterface(IID_IOleCommandTarget) failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    memset(&var, 0x0a, sizeof(var));
    hres = IOleCommandTarget_Exec(cmdtrg, NULL, OLECMDID_ONUNLOAD,
            OLECMDEXECOPT_DODEFAULT, NULL, &var);
    ok(hres == S_OK, "Exec(..., OLECMDID_ONUNLOAD, ...) failed: %08x\n", hres);
    ok(V_VT(&var) == VT_BOOL, "V_VT(var)=%d, expected VT_BOOL\n", V_VT(&var));
    ok(V_BOOL(&var) == VARIANT_TRUE, "V_BOOL(var)=%x, expected VARIANT_TRUE\n", V_BOOL(&var));

    hres = IOleCommandTarget_Exec(cmdtrg, NULL, OLECMDID_ONUNLOAD,
            OLECMDEXECOPT_DODEFAULT, NULL, NULL);
    ok(hres == S_OK, "Exec(..., OLECMDID_ONUNLOAD, ...) failed: %08x\n", hres);

    IOleCommandTarget_Release(cmdtrg);
}