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
typedef  int /*<<< orphan*/  IOleInPlaceSite ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IOleInPlaceSite ; 
 scalar_t__ IOleClientSite_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IOleInPlaceSite_OnUIActivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleInPlaceSite_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Invoke_ENABLED ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  client_site ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_ui_activate(void)
{
    IOleInPlaceSite *ip_site;
    HRESULT hres;

    hres = IOleClientSite_QueryInterface(client_site, &IID_IOleInPlaceSite, (void**)&ip_site);
    ok(hres == S_OK, "Could not get IOleInPlaceSite iface: %08x\n", hres);

    SET_EXPECT(Invoke_ENABLED);
    hres = IOleInPlaceSite_OnUIActivate(ip_site);
    ok(hres == S_OK, "OnUIActivate failed: %08x\n", hres);
    CLEAR_CALLED(Invoke_ENABLED); /* Not called on IE10 */

    IOleInPlaceSite_Release(ip_site);
}