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
typedef  int /*<<< orphan*/  IPersistStreamInit ;
typedef  int /*<<< orphan*/  IPersistMoniker ;
typedef  int /*<<< orphan*/  IPersistFile ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IPersistFile ; 
 int /*<<< orphan*/  IID_IPersistMoniker ; 
 int /*<<< orphan*/  IID_IPersistStreamInit ; 
 scalar_t__ IPersistFile_IsDirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistFile_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistMoniker_IsDirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStreamInit_IsDirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistStreamInit_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static void test_IsDirty(IHTMLDocument2 *doc, HRESULT exhres)
{
    IPersistStreamInit *perinit;
    IPersistMoniker *permon;
    IPersistFile *perfile;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IPersistStreamInit, (void**)&perinit);
    ok(hres == S_OK, "QueryInterface(IID_IPersistStreamInit failed: %08x\n", hres);
    if(SUCCEEDED(hres)) {
        hres = IPersistStreamInit_IsDirty(perinit);
        ok(hres == exhres, "IsDirty() = %08x, expected %08x\n", hres, exhres);
        IPersistStreamInit_Release(perinit);
    }

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IPersistMoniker, (void**)&permon);
    ok(hres == S_OK, "QueryInterface(IID_IPersistMoniker failed: %08x\n", hres);
    if(SUCCEEDED(hres)) {
        hres = IPersistMoniker_IsDirty(permon);
        ok(hres == exhres, "IsDirty() = %08x, expected %08x\n", hres, exhres);
        IPersistMoniker_Release(permon);
    }

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IPersistFile, (void**)&perfile);
    ok(hres == S_OK, "QueryInterface(IID_IPersistFile failed: %08x\n", hres);
    if(SUCCEEDED(hres)) {
        hres = IPersistFile_IsDirty(perfile);
        ok(hres == exhres, "IsDirty() = %08x, expected %08x\n", hres, exhres);
        IPersistFile_Release(perfile);
    }
}