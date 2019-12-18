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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IOmNavigator ;
typedef  int /*<<< orphan*/  IHTMLMimeTypesCollection ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLMimeTypesCollection_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLMimeTypesCollection_get_length (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IID_IHTMLMimeTypesCollection ; 
 scalar_t__ IOmNavigator_get_mimeTypes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_mime_types_col(IOmNavigator *nav)
{
    IHTMLMimeTypesCollection *col, *col2;
    LONG length;
    ULONG ref;
    HRESULT hres;

    hres = IOmNavigator_get_mimeTypes(nav, &col);
    ok(hres == S_OK, "get_mimeTypes failed: %08x\n", hres);

    hres = IOmNavigator_get_mimeTypes(nav, &col2);
    ok(hres == S_OK, "get_mimeTypes failed: %08x\n", hres);
    ok(iface_cmp((IUnknown*)col, (IUnknown*)col2), "col != col2\n");
    IHTMLMimeTypesCollection_Release(col2);

    test_disp((IUnknown*)col, &IID_IHTMLMimeTypesCollection, "[object]");

    length = 0xdeadbeef;
    hres = IHTMLMimeTypesCollection_get_length(col, &length);
    ok(hres == S_OK, "get_length failed: %08x\n", hres);
    ok(!length, "length = %d\n", length);

    ref = IHTMLMimeTypesCollection_Release(col);
    ok(!ref, "ref=%d\n", ref);
}