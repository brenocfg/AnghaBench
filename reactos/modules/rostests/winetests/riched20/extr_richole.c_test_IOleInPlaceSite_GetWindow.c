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
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  IOleInPlaceSite ;
typedef  int /*<<< orphan*/  IOleClientSite ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IOleInPlaceSite ; 
 scalar_t__ IOleClientSite_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleClientSite_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleInPlaceSite_GetWindow (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IOleInPlaceSite_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IRichEditOle_GetClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  create_interfaces (scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_IOleInPlaceSite_GetWindow(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  IOleClientSite *clientSite = NULL;
  IOleInPlaceSite *olePlace = NULL;
  HRESULT hres;
  HWND hwnd;

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  hres = IRichEditOle_GetClientSite(reOle, &clientSite);
  ok(hres == S_OK, "IRichEditOle_QueryInterface: 0x%08x\n", hres);

  hres = IOleClientSite_QueryInterface(clientSite, &IID_IOleInPlaceSite, (void **)&olePlace);
  ok(hres == S_OK, "IOleClientSite_QueryInterface: 0x%08x\n", hres);
  hres = IOleInPlaceSite_GetWindow(olePlace, &hwnd);
  ok(hres == S_OK, "IOleInPlaceSite_GetWindow: 0x%08x\n", hres);
  ok(w == hwnd, "got wrong pointer.\n");

  hres = IOleInPlaceSite_GetWindow(olePlace, NULL);
  ok(hres == E_INVALIDARG, "IOleInPlaceSite_GetWindow: 0x%08x\n", hres);

  IOleInPlaceSite_Release(olePlace);
  IOleClientSite_Release(clientSite);
  release_interfaces(&w, &reOle, &txtDoc, NULL);
}