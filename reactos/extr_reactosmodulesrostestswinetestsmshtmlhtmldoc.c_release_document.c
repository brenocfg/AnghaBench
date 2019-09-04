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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void release_document(IHTMLDocument2 *doc)
{
    IUnknown *unk;
    ULONG ref;
    HRESULT hres;

    /* Some broken IEs don't like if the last released reference is IHTMLDocument2 iface.
     * To workaround it, we release it via IUnknown iface */
    hres = IHTMLDocument2_QueryInterface(doc, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "Could not get IUnknown iface: %08x\n", hres);

    IHTMLDocument2_Release(doc);
    ref = IUnknown_Release(unk);
    ok(!ref, "ref = %d\n", ref);
}