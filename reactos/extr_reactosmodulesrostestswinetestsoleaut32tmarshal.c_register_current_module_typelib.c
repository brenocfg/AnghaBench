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
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadTypeLib (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RegisterTypeLib (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT register_current_module_typelib(void)
{
    WCHAR path[MAX_PATH];
    CHAR pathA[MAX_PATH];
    HRESULT hr;
    ITypeLib *typelib;

    GetModuleFileNameA(NULL, pathA, MAX_PATH);
    MultiByteToWideChar(CP_ACP, 0, pathA, -1, path, MAX_PATH);

    hr = LoadTypeLib(path, &typelib);
    if (SUCCEEDED(hr))
    {
        hr = RegisterTypeLib(typelib, path, NULL);
        ITypeLib_Release(typelib);
    }
    return hr;
}