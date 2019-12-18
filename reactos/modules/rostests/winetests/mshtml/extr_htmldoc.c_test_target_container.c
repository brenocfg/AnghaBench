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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITargetContainer ;
typedef  int /*<<< orphan*/  IOleContainer ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IOleContainer ; 
 int /*<<< orphan*/  IID_ITargetContainer ; 
 int /*<<< orphan*/  IOleContainer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITargetContainer_GetFramesContainer (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITargetContainer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_enum_objects (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_target_container(IHTMLDocument2 *doc)
{
    IOleContainer *ole_container, *doc_ole_container;
    ITargetContainer *target_container;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_ITargetContainer, (void**)&target_container);
    ok(hres == S_OK, "Could not get ITargetContainer iface: %08x\n", hres);

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleContainer, (void**)&doc_ole_container);
    ok(hres == S_OK, "Could not get ITargetContainer iface: %08x\n", hres);

    ole_container = (void*)0xdeadbeef;
    hres = ITargetContainer_GetFramesContainer(target_container, &ole_container);
    ok(hres == S_OK, "GetFramesContainer failed: %08x\n", hres);
    ok(ole_container != NULL, "ole_container == NULL\n");
    ok(iface_cmp((IUnknown*)ole_container, (IUnknown*)doc_ole_container), "ole_container != doc_ole_container\n");
    test_enum_objects(ole_container);
    IOleContainer_Release(ole_container);

    ITargetContainer_Release(target_container);
    IOleContainer_Release(doc_ole_container);
}