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
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int CLIENTSITE_DONTSET ; 
 int CLIENTSITE_SETNULL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetContainer ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 scalar_t__ IOleObject_Close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockContainer ; 
 int /*<<< orphan*/  OLECLOSE_NOSAVE ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 void* container_locked ; 
 void* expect_LockContainer_fLock ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_ClientSite (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_Close(IHTMLDocument2 *doc, BOOL set_client)
{
    IOleObject *oleobj = NULL;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleObject, (void**)&oleobj);
    ok(hres == S_OK, "QueryInterface(IID_IOleObject) failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    SET_EXPECT(GetContainer);
    SET_EXPECT(LockContainer);
    expect_LockContainer_fLock = FALSE;
    hres = IOleObject_Close(oleobj, OLECLOSE_NOSAVE);
    ok(hres == S_OK, "Close failed: %08x\n", hres);
    CHECK_CALLED(GetContainer);
    CHECK_CALLED(LockContainer);
    container_locked = FALSE;

    if(set_client)
        test_ClientSite(oleobj, CLIENTSITE_SETNULL|CLIENTSITE_DONTSET);

    IOleObject_Release(oleobj);
}