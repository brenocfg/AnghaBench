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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IAssemblyName ;
typedef  int /*<<< orphan*/  IAssemblyEnum ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_CACHE_GAC ; 
 int /*<<< orphan*/  ASM_CACHE_ROOT ; 
 int /*<<< orphan*/  CANOF_PARSE_DISPLAY_NAME ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/  IAssemblyEnum_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAssemblyName_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pCreateAssemblyEnum (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pCreateAssemblyNameObject (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_widechar (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_CreateAssemblyEnum(void)
{
    HRESULT hr;
    WCHAR namestr[MAX_PATH];
    IAssemblyEnum *asmenum;
    IAssemblyName *asmname;

    to_widechar(namestr, "wine");
    asmname = NULL;
    hr = pCreateAssemblyNameObject(&asmname, namestr, CANOF_PARSE_DISPLAY_NAME, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmname != NULL, "Expected non-NULL asmname\n");

    /* pEnum is NULL */
    if (0)
    {
        /* Crashes on .NET 1.x */
        hr = pCreateAssemblyEnum(NULL, NULL, asmname, ASM_CACHE_GAC, NULL);
        ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    }

    /* pName is NULL */
    asmenum = NULL;
    hr = pCreateAssemblyEnum(&asmenum, NULL, NULL, ASM_CACHE_GAC, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(asmenum != NULL, "Expected non-NULL asmenum\n");

    IAssemblyEnum_Release(asmenum);

    /* dwFlags is ASM_CACHE_ROOT */
    asmenum = (IAssemblyEnum *)0xdeadbeef;
    hr = pCreateAssemblyEnum(&asmenum, NULL, NULL, ASM_CACHE_ROOT, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    ok(asmenum == (IAssemblyEnum *)0xdeadbeef,
       "Expected asmenum to be unchanged, got %p\n", asmenum);

    /* invalid dwFlags */
    asmenum = (IAssemblyEnum *)0xdeadbeef;
    hr = pCreateAssemblyEnum(&asmenum, NULL, NULL, 0, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    ok(asmenum == (IAssemblyEnum *)0xdeadbeef,
       "Expected asmenum to be unchanged, got %p\n", asmenum);

    IAssemblyName_Release(asmname);
}