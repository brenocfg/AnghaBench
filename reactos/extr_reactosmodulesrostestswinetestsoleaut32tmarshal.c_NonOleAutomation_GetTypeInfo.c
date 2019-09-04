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
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IID_INonOleAutomation ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIBID_TestTypelib ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int /*<<< orphan*/  LoadRegTypeLib (int /*<<< orphan*/ *,int,int,...) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **)) ; 

__attribute__((used)) static ITypeInfo *NonOleAutomation_GetTypeInfo(void)
{
    ITypeLib *pTypeLib;
    HRESULT hr = LoadRegTypeLib(&LIBID_TestTypelib, 2, 5, LOCALE_NEUTRAL, &pTypeLib);
    ok_ole_success(hr, LoadRegTypeLib);
    if (SUCCEEDED(hr))
    {
        ITypeInfo *pTypeInfo;
        hr = ITypeLib_GetTypeInfoOfGuid(pTypeLib, &IID_INonOleAutomation, &pTypeInfo);
        ok_ole_success(hr, ITypeLib_GetTypeInfoOfGuid);
        ITypeLib_Release(pTypeLib);
        return pTypeInfo;
    }
    return NULL;
}