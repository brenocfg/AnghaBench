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
typedef  char WCHAR ;
typedef  void ITypeLib ;
typedef  void* HRESULT ;

/* Variables and functions */
 void* E_INVALIDARG ; 
 void* LoadTypeLib (char const*,void**) ; 
 void* LoadTypeLibEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  REGKIND_NONE ; 
 void* TYPE_E_CANTLOADLIBRARY ; 
 int /*<<< orphan*/  ok (int,char*,void*) ; 

__attribute__((used)) static void test_LoadTypeLib(void)
{
    ITypeLib *tl;
    HRESULT hres;

    static const WCHAR kernel32_dllW[] = {'k','e','r','n','e','l','3','2','.','d','l','l',0};

    hres = LoadTypeLib(kernel32_dllW, &tl);
    ok(hres == TYPE_E_CANTLOADLIBRARY, "LoadTypeLib returned: %08x, expected TYPE_E_CANTLOADLIBRARY\n", hres);

    hres = LoadTypeLib(NULL, NULL);
    ok(hres == E_INVALIDARG, "Got %#x.\n", hres);

    tl = (void *)0xdeadbeef;
    hres = LoadTypeLib(NULL, &tl);
    ok(hres == E_INVALIDARG, "Got %#x.\n", hres);
    ok(tl == (void *)0xdeadbeef, "Got %p.\n", tl);

    hres = LoadTypeLibEx(NULL, REGKIND_NONE, NULL);
    ok(hres == E_INVALIDARG, "Got %#x.\n", hres);

    tl = (void *)0xdeadbeef;
    hres = LoadTypeLibEx(NULL, REGKIND_NONE, &tl);
    ok(hres == E_INVALIDARG, "Got %#x.\n", hres);
    ok(tl == (void *)0xdeadbeef, "Got %p.\n", tl);
}