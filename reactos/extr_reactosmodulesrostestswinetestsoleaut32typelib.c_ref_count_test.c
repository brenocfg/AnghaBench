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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ ITypeLib_GetTypeInfo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int ITypeLib_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadTypeLib (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void ref_count_test(LPCWSTR type_lib)
{
    ITypeLib *iface;
    ITypeInfo *iti1, *iti2;
    HRESULT hRes;
    int ref_count;

    trace("Loading type library\n");
    hRes = LoadTypeLib(type_lib, &iface);
    ok(hRes == S_OK, "Could not load type library\n");
    if(hRes != S_OK)
        return;

    hRes = ITypeLib_GetTypeInfo(iface, 1, &iti1);
    ok(hRes == S_OK, "ITypeLib_GetTypeInfo failed on index = 1\n");
    ref_count = ITypeLib_Release(iface);
    ok(ref_count > 0, "ITypeLib destroyed while ITypeInfo has back pointer\n");
    if(!ref_count)
        return;

    hRes = ITypeLib_GetTypeInfo(iface, 1, &iti2);
    ok(hRes == S_OK, "ITypeLib_GetTypeInfo failed on index = 1\n");
    ok(iti1 == iti2, "ITypeLib_GetTypeInfo returned different pointers for same indexes\n");

    ITypeLib_AddRef(iface);
    ITypeInfo_Release(iti2);
    ITypeInfo_Release(iti1);
    ok(ITypeLib_Release(iface) == 0, "ITypeLib should be destroyed here.\n");
}