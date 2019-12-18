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
typedef  int UINT ;
typedef  char OLECHAR ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo2 ;
typedef  int /*<<< orphan*/  ICreateTypeLib2 ;
typedef  int /*<<< orphan*/  ICreateTypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTypeLib2 (int /*<<< orphan*/ *,char const*,int*) ; 
 int /*<<< orphan*/  ICreateTypeInfo2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  ICreateTypeInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ICreateTypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICreateTypeLib2_CreateTypeInfo (int /*<<< orphan*/ *,char*,int*,...) ; 
 int /*<<< orphan*/  ICreateTypeLib2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ITypeInfo2 ; 
 int /*<<< orphan*/  ITypeInfo2_GetContainingTypeLib (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  ITypeInfo2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_WIN32 ; 
 int /*<<< orphan*/  TKIND_DISPATCH ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*)) ; 

__attribute__((used)) static void test_TypeInfo2_GetContainingTypeLib(void)
{
    static const WCHAR test[] = {'t','e','s','t','.','t','l','b',0};
    static OLECHAR testTI[] = {'t','e','s','t','T','y','p','e','I','n','f','o',0};

    ICreateTypeLib2 *ctl2;
    ICreateTypeInfo *cti;
    ITypeInfo2 *ti2;
    ITypeLib *tl;
    UINT Index;
    HRESULT hr;

    hr = CreateTypeLib2(SYS_WIN32, test, &ctl2);
    ok_ole_success(hr, CreateTypeLib2);

    hr = ICreateTypeLib2_CreateTypeInfo(ctl2, testTI, TKIND_DISPATCH, &cti);
    ok_ole_success(hr, ICreateTypeLib2_CreateTypeInfo);

    hr = ICreateTypeInfo_QueryInterface(cti, &IID_ITypeInfo2, (void**)&ti2);
    ok_ole_success(hr, ICreateTypeInfo2_QueryInterface);

    tl = NULL;
    Index = 888;
    hr = ITypeInfo2_GetContainingTypeLib(ti2, &tl, &Index);
    ok_ole_success(hr, ITypeInfo2_GetContainingTypeLib);
    ok(tl != NULL, "ITypeInfo2_GetContainingTypeLib returned empty TypeLib\n");
    ok(Index == 0, "ITypeInfo2_GetContainingTypeLib returned Index = %u, expected 0\n", Index);
    if(tl) ITypeLib_Release(tl);

    tl = NULL;
    hr = ITypeInfo2_GetContainingTypeLib(ti2, &tl, NULL);
    ok_ole_success(hr, ITypeInfo2_GetContainingTypeLib);
    ok(tl != NULL, "ITypeInfo2_GetContainingTypeLib returned empty TypeLib\n");
    if(tl) ITypeLib_Release(tl);

    Index = 888;
    hr = ITypeInfo2_GetContainingTypeLib(ti2, NULL, &Index);
    ok_ole_success(hr, ITypeInfo2_GetContainingTypeLib);
    ok(Index == 0, "ITypeInfo2_GetContainingTypeLib returned Index = %u, expected 0\n", Index);

    hr = ITypeInfo2_GetContainingTypeLib(ti2, NULL, NULL);
    ok_ole_success(hr, ITypeInfo2_GetContainingTypeLib);

    ITypeInfo2_Release(ti2);
    ICreateTypeInfo_Release(cti);
    ICreateTypeLib2_Release(ctl2);
}