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
typedef  int ULONG ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IOmNavigator ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLPluginsCollection ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DIID_DispCPlugins ; 
 int IHTMLPluginsCollection_Release (int /*<<< orphan*/ *) ; 
 int IHTMLPluginsCollection_get_length (int /*<<< orphan*/ *,int*) ; 
 int IHTMLPluginsCollection_refresh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int IHTMLWindow2_get_navigator (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLPluginsCollection ; 
 int /*<<< orphan*/  IOmNavigator_Release (int /*<<< orphan*/ *) ; 
 int IOmNavigator_get_plugins (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int S_OK ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/ * get_doc_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_disp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_plugins_col(IHTMLDocument2 *doc)
{
    IHTMLPluginsCollection *col, *col2;
    IHTMLWindow2 *window;
    IOmNavigator *nav;
    ULONG ref;
    LONG len;
    HRESULT hres;

    window = get_doc_window(doc);
    hres = IHTMLWindow2_get_navigator(window, &nav);
    ok(hres == S_OK, "get_navigator failed: %08x\n", hres);
    IHTMLWindow2_Release(window);

    hres = IOmNavigator_get_plugins(nav, &col);
    ok(hres == S_OK, "get_plugins failed: %08x\n", hres);

    hres = IOmNavigator_get_plugins(nav, &col2);
    ok(hres == S_OK, "get_plugins failed: %08x\n", hres);
    ok(iface_cmp((IUnknown*)col, (IUnknown*)col2), "col != col2\n");
    IHTMLPluginsCollection_Release(col2);

    test_disp2((IUnknown*)col, &DIID_DispCPlugins, &IID_IHTMLPluginsCollection, "[object]");

    len = 0xdeadbeef;
    hres = IHTMLPluginsCollection_get_length(col, &len);
    ok(hres == S_OK, "get_length failed: %08x\n", hres);
    ok(!len, "length = %d\n", len);

    hres = IHTMLPluginsCollection_refresh(col, VARIANT_FALSE);
    ok(hres == S_OK, "refresh failed: %08x\n", hres);

    hres = IHTMLPluginsCollection_refresh(col, VARIANT_TRUE);
    ok(hres == S_OK, "refresh failed: %08x\n", hres);

    ref = IHTMLPluginsCollection_Release(col);
    ok(!ref, "ref=%d\n", ref);

    IOmNavigator_Release(nav);
}