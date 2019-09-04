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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IPersistStreamInit ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IPersistStreamInit ; 
 scalar_t__ IPersistStreamInit_InitNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistStreamInit_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  resetting_document ; 
 int /*<<< orphan*/  test_GetCurMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_document(IHTMLDocument2 *doc)
{
    IPersistStreamInit *init;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IPersistStreamInit, (void**)&init);
    ok(hres == S_OK, "QueryInterface(IID_IPersistStreamInit) failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    resetting_document = TRUE;

    hres = IPersistStreamInit_InitNew(init);
    ok(hres == S_OK, "Load failed: %08x\n", hres);

    resetting_document = FALSE;

    test_GetCurMoniker((IUnknown*)doc, NULL, "about:blank", FALSE);

    IPersistStreamInit_Release(init);
}