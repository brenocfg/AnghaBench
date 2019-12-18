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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_TF_CategoryMgr ; 
 int /*<<< orphan*/  CLSID_TF_InputProcessorProfiles ; 
 int /*<<< orphan*/  CLSID_TF_ThreadMgr ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  IID_ITfCategoryMgr ; 
 int /*<<< orphan*/  IID_ITfInputProcessorProfiles ; 
 int /*<<< orphan*/  IID_ITfThreadMgr ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cm ; 
 int /*<<< orphan*/  g_ipp ; 
 int /*<<< orphan*/  g_tm ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static HRESULT initialize(void)
{
    HRESULT hr;
    HKEY hkey;

    CoInitialize(NULL);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\CTF\\TIP", 0,
                      KEY_READ|KEY_WRITE, &hkey) != ERROR_SUCCESS)
    {
        skip("Not enough permission to register input processor\n");
        return E_FAIL;
    }
    RegCloseKey(hkey);

    hr = CoCreateInstance (&CLSID_TF_InputProcessorProfiles, NULL,
          CLSCTX_INPROC_SERVER, &IID_ITfInputProcessorProfiles, (void**)&g_ipp);
    if (SUCCEEDED(hr))
        hr = CoCreateInstance (&CLSID_TF_CategoryMgr, NULL,
          CLSCTX_INPROC_SERVER, &IID_ITfCategoryMgr, (void**)&g_cm);
    if (SUCCEEDED(hr))
        hr = CoCreateInstance (&CLSID_TF_ThreadMgr, NULL,
          CLSCTX_INPROC_SERVER, &IID_ITfThreadMgr, (void**)&g_tm);
    return hr;
}