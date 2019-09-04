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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/  ExtendedProxyFileInfo ;

/* Variables and functions */
 scalar_t__ E_ACCESSDENIED ; 
 scalar_t__ E_HANDLE ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/ * GetModuleHandleA (int /*<<< orphan*/ *) ; 
 scalar_t__ NdrDllRegisterProxy (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 scalar_t__ NdrDllUnregisterProxy (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  const** proxy_file_list ; 
 int /*<<< orphan*/  const** proxy_file_list2 ; 

__attribute__((used)) static void test_NdrDllRegisterProxy( void )
{
    HRESULT res;
    const ExtendedProxyFileInfo *pf;
    HMODULE hmod = GetModuleHandleA(NULL);


    res = NdrDllRegisterProxy(NULL, NULL, NULL);
    ok(res == E_HANDLE, "Incorrect return code %x\n",res);
    pf = NULL;
    res = NdrDllRegisterProxy(hmod, &pf, NULL);
    ok(res == E_NOINTERFACE, "Incorrect return code %x\n",res);
    res = NdrDllRegisterProxy(hmod, proxy_file_list2, NULL);
    ok(res == E_NOINTERFACE, "Incorrect return code %x\n",res);
    /* This fails on Vista and Windows 7 due to permissions */
    res = NdrDllRegisterProxy(hmod, proxy_file_list, NULL);
    ok(res == S_OK || res == E_ACCESSDENIED, "NdrDllRegisterProxy failed %x\n",res);
    if (res == S_OK)
    {
        res = NdrDllUnregisterProxy(hmod,proxy_file_list, NULL);
        ok(res == S_OK, "NdrDllUnregisterProxy failed %x\n",res);
    }
}