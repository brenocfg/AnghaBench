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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  IOleWindow ;
typedef  int /*<<< orphan*/  IOleInPlaceSite ;
typedef  int /*<<< orphan*/  IOleClientSite ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IOleClientSite ; 
 int /*<<< orphan*/  IID_IOleInPlaceSite ; 
 int /*<<< orphan*/  IID_IOleWindow ; 
 int /*<<< orphan*/  IID_IRichEditOle ; 
 scalar_t__ IOleClientSite_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleClientSite_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleInPlaceSite_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleWindow_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleWindow_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IRichEditOle_GetClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ get_refcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetClientSite(void)
{
  HWND w;
  IRichEditOle *reOle = NULL, *reOle1 = NULL;
  ITextDocument *txtDoc = NULL;
  IOleClientSite *clientSite = NULL, *clientSite1 = NULL, *clientSite2 = NULL;
  IOleWindow *oleWin = NULL, *oleWin1 = NULL;
  IOleInPlaceSite *olePlace = NULL, *olePlace1 = NULL;
  HRESULT hres;
  LONG refcount1, refcount2;

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  hres = IRichEditOle_GetClientSite(reOle, &clientSite);
  ok(hres == S_OK, "IRichEditOle_QueryInterface: 0x%08x\n", hres);
  EXPECT_REF(clientSite, 1);

  hres = IOleClientSite_QueryInterface(clientSite, &IID_IRichEditOle, (void **)&reOle1);
  ok(hres == E_NOINTERFACE, "IOleClientSite_QueryInterface: %x\n", hres);

  hres = IRichEditOle_GetClientSite(reOle, &clientSite1);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(clientSite != clientSite1, "got %p, %p\n", clientSite, clientSite1);
  IOleClientSite_Release(clientSite1);

  hres = IOleClientSite_QueryInterface(clientSite, &IID_IOleClientSite, (void **)&clientSite1);
  ok(hres == S_OK, "IOleClientSite_QueryInterface: 0x%08x\n", hres);
  ok(clientSite == clientSite1, "Should not return a new pointer.\n");
  EXPECT_REF(clientSite, 2);

  /* IOleWindow interface */
  hres = IOleClientSite_QueryInterface(clientSite, &IID_IOleWindow, (void **)&oleWin);
  ok(hres == S_OK, "IOleClientSite_QueryInterface: 0x%08x\n", hres);
  refcount1 = get_refcount((IUnknown *)clientSite);
  refcount2 = get_refcount((IUnknown *)oleWin);
  ok(refcount1 == refcount2, "got wrong ref count.\n");

  hres = IOleClientSite_QueryInterface(clientSite, &IID_IOleWindow, (void **)&oleWin1);
  ok(hres == S_OK, "IOleClientSite_QueryInterface: 0x%08x\n", hres);
  ok(oleWin == oleWin1, "Should not return a new pointer.\n");
  refcount1 = get_refcount((IUnknown *)clientSite);
  refcount2 = get_refcount((IUnknown *)oleWin);
  ok(refcount1 == refcount2, "got wrong ref count.\n");

  hres = IOleWindow_QueryInterface(oleWin, &IID_IOleClientSite, (void **)&clientSite2);
  ok(hres == S_OK, "IOleWindow_QueryInterface: 0x%08x\n", hres);
  ok(clientSite2 == clientSite1, "got wrong pointer\n");

  /* IOleInPlaceSite interface */
  hres = IOleClientSite_QueryInterface(clientSite, &IID_IOleInPlaceSite, (void **)&olePlace);
  ok(hres == S_OK, "IOleClientSite_QueryInterface: 0x%08x\n", hres);
  refcount1 = get_refcount((IUnknown *)olePlace);
  refcount2 = get_refcount((IUnknown *)clientSite);
  ok(refcount1 == refcount2, "got wrong ref count.\n");

  hres = IOleClientSite_QueryInterface(clientSite, &IID_IOleInPlaceSite, (void **)&olePlace1);
  ok(hres == S_OK, "IOleClientSite_QueryInterface: 0x%08x\n", hres);
  ok(olePlace == olePlace1, "Should not return a new pointer.\n");
  IOleInPlaceSite_Release(olePlace1);

  hres = IOleWindow_QueryInterface(oleWin, &IID_IOleInPlaceSite, (void **)&olePlace1);
  ok(hres == S_OK, "IOleWindow_QueryInterface: 0x%08x\n", hres);
  refcount1 = get_refcount((IUnknown *)olePlace1);
  refcount2 = get_refcount((IUnknown *)oleWin);
  ok(refcount1 == refcount2, "got wrong ref count.\n");

  IOleInPlaceSite_Release(olePlace1);
  IOleInPlaceSite_Release(olePlace);
  IOleWindow_Release(oleWin1);
  IOleWindow_Release(oleWin);
  IOleClientSite_Release(clientSite2);
  IOleClientSite_Release(clientSite1);
  IOleClientSite_Release(clientSite);
  release_interfaces(&w, &reOle, &txtDoc, NULL);
}