#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct expected_method {char* member_0; int /*<<< orphan*/  const member_1; } ;
struct TYPE_4__ {int lindex; void* tymed; scalar_t__ cfFormat; void* dwAspect; int /*<<< orphan*/ * ptd; } ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IOleClientSite ;
typedef  int HRESULT ;
typedef  TYPE_1__ FORMATETC ;

/* Variables and functions */
 scalar_t__ CF_TEXT ; 
 int /*<<< orphan*/  CHECK_NO_EXTRA_METHODS () ; 
 int /*<<< orphan*/  CLSID_Equation3 ; 
 void* DVASPECT_CONTENT ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OLERENDER_ASIS ; 
 int /*<<< orphan*/  OLERENDER_DRAW ; 
 int /*<<< orphan*/  OLERENDER_FORMAT ; 
 int /*<<< orphan*/  OLERENDER_NONE ; 
 int OleCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  OleObjectCache ; 
 int /*<<< orphan*/  OleObjectRunnable ; 
 int S_OK ; 
#define  TEST_OPTIONAL 128 
 void* TYMED_HGLOBAL ; 
 void* TYMED_NULL ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * cache ; 
 struct expected_method const* expected_method_list ; 
 int g_GetMiscStatusFailsWith ; 
 TYPE_1__* g_expected_fetc ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  ok_ole_success (int,char*) ; 
 int /*<<< orphan*/ * runnable ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_OleCreate(IStorage *pStorage)
{
    HRESULT hr;
    IOleObject *pObject;
    FORMATETC formatetc;
    static const struct expected_method methods_olerender_none[] =
    {
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", TEST_OPTIONAL },
        { "OleObject_Release", TEST_OPTIONAL },
        { "OleObject_QueryInterface", TEST_OPTIONAL },
        { "OleObjectPersistStg_AddRef", 0 },
        { "OleObjectPersistStg_InitNew", 0 },
        { "OleObjectPersistStg_Release", 0 },
        { "OleObject_Release", 0 },
        { "OleObject_Release", TEST_OPTIONAL },
        { NULL, 0 }
    };
    static const struct expected_method methods_olerender_draw[] =
    {
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", TEST_OPTIONAL /* NT4 only */ },
        { "OleObject_Release", TEST_OPTIONAL /* NT4 only */ },
        { "OleObject_QueryInterface", TEST_OPTIONAL /* NT4 only */ },
        { "OleObjectPersistStg_AddRef", 0 },
        { "OleObjectPersistStg_InitNew", 0 },
        { "OleObjectPersistStg_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectRunnable_AddRef", 0 },
        { "OleObjectRunnable_Run", 0 },
        { "OleObjectRunnable_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectCache_AddRef", 0 },
        { "OleObjectCache_Cache", 0 },
        { "OleObjectCache_Release", 0 },
        { "OleObject_Release", 0 },
        { "OleObject_Release", TEST_OPTIONAL /* NT4 only */ },
        { NULL, 0 }
    };
    static const struct expected_method methods_olerender_draw_with_site[] =
    {
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_GetMiscStatus", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectPersistStg_AddRef", 0 },
        { "OleObjectPersistStg_InitNew", 0 },
        { "OleObjectPersistStg_Release", 0 },
        { "OleObject_SetClientSite", 0 },
        { "OleObject_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectRunnable_AddRef", 0 },
        { "OleObjectRunnable_Run", 0 },
        { "OleObjectRunnable_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectCache_AddRef", 0 },
        { "OleObjectCache_Cache", 0 },
        { "OleObjectCache_Release", 0 },
        { "OleObject_Release", 0 },
        { NULL, 0 }
    };
    static const struct expected_method methods_olerender_format[] =
    {
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_GetMiscStatus", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectPersistStg_AddRef", 0 },
        { "OleObjectPersistStg_InitNew", 0 },
        { "OleObjectPersistStg_Release", 0 },
        { "OleObject_SetClientSite", 0 },
        { "OleObject_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectRunnable_AddRef", 0 },
        { "OleObjectRunnable_Run", 0 },
        { "OleObjectRunnable_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectCache_AddRef", 0 },
        { "OleObjectCache_Cache", 0 },
        { "OleObjectCache_Release", 0 },
        { "OleObject_Release", 0 },
        { NULL, 0 }
    };
    static const struct expected_method methods_olerender_asis[] =
    {
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", TEST_OPTIONAL /* NT4 only */ },
        { "OleObject_Release", TEST_OPTIONAL /* NT4 only */ },
        { "OleObject_QueryInterface", TEST_OPTIONAL /* NT4 only */ },
        { "OleObjectPersistStg_AddRef", 0 },
        { "OleObjectPersistStg_InitNew", 0 },
        { "OleObjectPersistStg_Release", 0 },
        { "OleObject_Release", 0 },
        { "OleObject_Release", TEST_OPTIONAL /* NT4 only */ },
        { NULL, 0 }
    };
    static const struct expected_method methods_olerender_draw_no_runnable[] =
    {
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", TEST_OPTIONAL /* NT4 only */ },
        { "OleObject_Release", TEST_OPTIONAL /* NT4 only */ },
        { "OleObject_QueryInterface", TEST_OPTIONAL /* NT4 only */ },
        { "OleObjectPersistStg_AddRef", 0 },
        { "OleObjectPersistStg_InitNew", 0 },
        { "OleObjectPersistStg_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectCache_AddRef", 0 },
        { "OleObjectCache_Cache", 0 },
        { "OleObjectCache_Release", 0 },
        { "OleObject_Release", 0 },
        { "OleObject_Release", TEST_OPTIONAL /* NT4 only */ },
        { NULL, 0 },
    };
    static const struct expected_method methods_olerender_draw_no_cache[] =
    {
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_AddRef", TEST_OPTIONAL /* NT4 only */ },
        { "OleObject_Release", TEST_OPTIONAL /* NT4 only */ },
        { "OleObject_QueryInterface", TEST_OPTIONAL /* NT4 only */ },
        { "OleObjectPersistStg_AddRef", 0 },
        { "OleObjectPersistStg_InitNew", 0 },
        { "OleObjectPersistStg_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObjectRunnable_AddRef", 0 },
        { "OleObjectRunnable_Run", 0 },
        { "OleObjectRunnable_Release", 0 },
        { "OleObject_QueryInterface", 0 },
        { "OleObject_Release", 0 },
        { "OleObject_Release", TEST_OPTIONAL /* NT4 only */ },
        { NULL, 0 }
    };

    g_expected_fetc = &formatetc;
    formatetc.cfFormat = 0;
    formatetc.ptd = NULL;
    formatetc.dwAspect = DVASPECT_CONTENT;
    formatetc.lindex = -1;
    formatetc.tymed = TYMED_NULL;
    runnable = &OleObjectRunnable;
    cache = &OleObjectCache;
    expected_method_list = methods_olerender_none;
    trace("OleCreate with OLERENDER_NONE:\n");
    hr = OleCreate(&CLSID_Equation3, &IID_IOleObject, OLERENDER_NONE, NULL, NULL, pStorage, (void **)&pObject);
    ok_ole_success(hr, "OleCreate");
    IOleObject_Release(pObject);
    CHECK_NO_EXTRA_METHODS();

    expected_method_list = methods_olerender_draw;
    trace("OleCreate with OLERENDER_DRAW:\n");
    hr = OleCreate(&CLSID_Equation3, &IID_IOleObject, OLERENDER_DRAW, NULL, NULL, pStorage, (void **)&pObject);
    ok_ole_success(hr, "OleCreate");
    IOleObject_Release(pObject);
    CHECK_NO_EXTRA_METHODS();

    expected_method_list = methods_olerender_draw_with_site;
    trace("OleCreate with OLERENDER_DRAW, with site:\n");
    hr = OleCreate(&CLSID_Equation3, &IID_IOleObject, OLERENDER_DRAW, NULL, (IOleClientSite*)0xdeadbeef, pStorage, (void **)&pObject);
    ok_ole_success(hr, "OleCreate");
    IOleObject_Release(pObject);
    CHECK_NO_EXTRA_METHODS();

    /* GetMiscStatus fails */
    g_GetMiscStatusFailsWith = 0x8fafefaf;
    expected_method_list = methods_olerender_draw_with_site;
    trace("OleCreate with OLERENDER_DRAW, with site:\n");
    hr = OleCreate(&CLSID_Equation3, &IID_IOleObject, OLERENDER_DRAW, NULL, (IOleClientSite*)0xdeadbeef, pStorage, (void **)&pObject);
    ok_ole_success(hr, "OleCreate");
    IOleObject_Release(pObject);
    CHECK_NO_EXTRA_METHODS();
    g_GetMiscStatusFailsWith = S_OK;

    formatetc.cfFormat = CF_TEXT;
    formatetc.ptd = NULL;
    formatetc.dwAspect = DVASPECT_CONTENT;
    formatetc.lindex = -1;
    formatetc.tymed = TYMED_HGLOBAL;
    expected_method_list = methods_olerender_format;
    trace("OleCreate with OLERENDER_FORMAT:\n");
    hr = OleCreate(&CLSID_Equation3, &IID_IOleObject, OLERENDER_FORMAT, &formatetc, (IOleClientSite *)0xdeadbeef, pStorage, (void **)&pObject);
    ok(hr == S_OK ||
       broken(hr == E_INVALIDARG), /* win2k */
       "OleCreate failed with error 0x%08x\n", hr);
    if (pObject)
    {
        IOleObject_Release(pObject);
        CHECK_NO_EXTRA_METHODS();
    }

    expected_method_list = methods_olerender_asis;
    trace("OleCreate with OLERENDER_ASIS:\n");
    hr = OleCreate(&CLSID_Equation3, &IID_IOleObject, OLERENDER_ASIS, NULL, NULL, pStorage, (void **)&pObject);
    ok_ole_success(hr, "OleCreate");
    IOleObject_Release(pObject);
    CHECK_NO_EXTRA_METHODS();

    formatetc.cfFormat = 0;
    formatetc.tymed = TYMED_NULL;
    runnable = NULL;
    expected_method_list = methods_olerender_draw_no_runnable;
    trace("OleCreate with OLERENDER_DRAW (no IRunnableObject):\n");
    hr = OleCreate(&CLSID_Equation3, &IID_IOleObject, OLERENDER_DRAW, NULL, NULL, pStorage, (void **)&pObject);
    ok_ole_success(hr, "OleCreate");
    IOleObject_Release(pObject);
    CHECK_NO_EXTRA_METHODS();

    runnable = &OleObjectRunnable;
    cache = NULL;
    expected_method_list = methods_olerender_draw_no_cache;
    trace("OleCreate with OLERENDER_DRAW (no IOleCache):\n");
    hr = OleCreate(&CLSID_Equation3, &IID_IOleObject, OLERENDER_DRAW, NULL, NULL, pStorage, (void **)&pObject);
    ok_ole_success(hr, "OleCreate");
    IOleObject_Release(pObject);
    CHECK_NO_EXTRA_METHODS();
    trace("end\n");
    g_expected_fetc = NULL;
}