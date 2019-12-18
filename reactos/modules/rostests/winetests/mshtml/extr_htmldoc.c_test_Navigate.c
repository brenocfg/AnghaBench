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
typedef  int /*<<< orphan*/  IHlinkTarget ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateMe ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IHlinkTarget_Navigate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlinkTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHlinkTarget ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_Navigate(IHTMLDocument2 *doc)
{
    IHlinkTarget *hlink;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHlinkTarget, (void**)&hlink);
    ok(hres == S_OK, "QueryInterface(IID_IHlinkTarget) failed: %08x\n", hres);

    SET_EXPECT(ActivateMe);
    hres = IHlinkTarget_Navigate(hlink, 0, NULL);
    ok(hres == S_OK, "Navigate failed: %08x\n", hres);
    CHECK_CALLED(ActivateMe);

    IHlinkTarget_Release(hlink);
}