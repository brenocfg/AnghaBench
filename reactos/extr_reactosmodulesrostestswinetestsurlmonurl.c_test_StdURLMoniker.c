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
typedef  int /*<<< orphan*/  LPOLESTR ;
typedef  int /*<<< orphan*/  IUriContainer ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/ * CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * CreateAsyncBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAsyncMoniker ; 
 int /*<<< orphan*/  IID_IInternet ; 
 int /*<<< orphan*/  IID_IMoniker ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IID_IUriContainer ; 
 int /*<<< orphan*/ * IMoniker_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IMoniker_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IUriContainer_GetIUri (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUriContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MK_E_SYNTAX ; 
 int /*<<< orphan*/  QueryInterface_IServiceProvider ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * S_FALSE ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  bsc ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCreateUri ; 

__attribute__((used)) static void test_StdURLMoniker(void)
{
    IMoniker *mon, *async_mon;
    LPOLESTR display_name;
    IBindCtx *bctx;
    IUnknown *unk;
    HRESULT hres;

    hres = CoCreateInstance(&IID_IInternet, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IMoniker, (void**)&mon);
    ok(hres == S_OK, "Could not create IInternet instance: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IMoniker_QueryInterface(mon, &IID_IAsyncMoniker, (void**)&async_mon);
    ok(hres == S_OK, "Could not get IAsyncMoniker iface: %08x\n", hres);
    ok(mon == async_mon, "mon != async_mon\n");
    IMoniker_Release(async_mon);

    hres = IMoniker_GetDisplayName(mon, NULL, NULL, &display_name);
    ok(hres == E_OUTOFMEMORY, "GetDisplayName failed: %08x, expected E_OUTOFMEMORY\n", hres);

    if(pCreateUri) {
      IUriContainer *uri_container;
      IUri *uri;

      hres = IMoniker_QueryInterface(mon, &IID_IUriContainer, (void**)&uri_container);
      ok(hres == S_OK, "Could not get IUriMoniker iface: %08x\n", hres);


      uri = (void*)0xdeadbeef;
      hres = IUriContainer_GetIUri(uri_container, &uri);
      ok(hres == S_FALSE, "GetIUri failed: %08x\n", hres);
      ok(!uri, "uri = %p, expected NULL\n", uri);

      IUriContainer_Release(uri_container);
    }

    SET_EXPECT(QueryInterface_IServiceProvider);
    hres = CreateAsyncBindCtx(0, (IBindStatusCallback*)&bsc, NULL, &bctx);
    ok(hres == S_OK, "CreateAsyncBindCtx failed: %08x\n\n", hres);
    CHECK_CALLED(QueryInterface_IServiceProvider);

    if(pCreateUri) { /* Skip these tests on old IEs */
        unk = (void*)0xdeadbeef;
        hres = IMoniker_BindToStorage(mon, bctx, NULL, &IID_IStream, (void**)&unk);
        ok(hres == MK_E_SYNTAX, "BindToStorage failed: %08x, expected MK_E_SYNTAX\n", hres);
        ok(!unk, "unk = %p\n", unk);

        unk = (void*)0xdeadbeef;
        hres = IMoniker_BindToObject(mon, bctx, NULL, &IID_IUnknown, (void**)&unk);
        ok(hres == MK_E_SYNTAX, "BindToStorage failed: %08x, expected MK_E_SYNTAX\n", hres);
        ok(!unk, "unk = %p\n", unk);
    }

    IMoniker_Release(mon);
}