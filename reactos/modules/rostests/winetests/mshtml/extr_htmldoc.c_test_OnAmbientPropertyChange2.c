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
typedef  int /*<<< orphan*/  IOleControl ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_AMBIENT_PALETTE ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IOleControl ; 
 scalar_t__ IOleControl_OnAmbientPropertyChange (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOleControl_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_OnAmbientPropertyChange2(IHTMLDocument2 *doc)
{
    IOleControl *control = NULL;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleControl, (void**)&control);
    ok(hres == S_OK, "QueryInterface(IID_IOleControl failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IOleControl_OnAmbientPropertyChange(control, DISPID_AMBIENT_PALETTE);
    ok(hres == S_OK, "OnAmbientPropertyChange failed: %08x\n", hres);

    IOleControl_Release(control);
}