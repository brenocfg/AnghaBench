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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  IVdsServiceLoader ;
typedef  int /*<<< orphan*/  IVdsService ;
typedef  int /*<<< orphan*/  IEnumVdsObject ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int CLSCTX_LOCAL_SERVER ; 
 int CLSCTX_REMOTE_SERVER ; 
 int /*<<< orphan*/  CLSID_VdsLoader ; 
 int /*<<< orphan*/  COINIT_APARTMENTTHREADED ; 
 int /*<<< orphan*/  CheckDriveIndex (int /*<<< orphan*/ ) ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoInitializeSecurity (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IVdsServiceLoader ; 
 scalar_t__ IVdsServiceLoader_LoadService (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IVdsServiceLoader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsService_CleanupObsoleteMountPoints (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsService_QueryProviders (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IVdsService_Reenumerate (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsService_Refresh (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsService_WaitForServiceReady (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_C_AUTHN_LEVEL_CONNECT ; 
 int /*<<< orphan*/  RPC_C_IMP_LEVEL_IMPERSONATE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VDS_QUERY_SOFTWARE_PROVIDERS ; 
 int /*<<< orphan*/  VDS_SET_ERROR (scalar_t__) ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnsprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

BOOL RefreshLayout(DWORD DriveIndex)
{
	BOOL r = FALSE;
	HRESULT hr;
	wchar_t wPhysicalName[24];
	IVdsServiceLoader *pLoader;
	IVdsService *pService;
	IEnumVdsObject *pEnum;

	CheckDriveIndex(DriveIndex);
	wnsprintf(wPhysicalName, ARRAYSIZE(wPhysicalName), L"\\\\?\\PhysicalDrive%lu", DriveIndex);

	// Initialize COM
	IGNORE_RETVAL(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED));
	IGNORE_RETVAL(CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_CONNECT,
		RPC_C_IMP_LEVEL_IMPERSONATE, NULL, 0, NULL));

	// Create a VDS Loader Instance
	hr = CoCreateInstance(&CLSID_VdsLoader, NULL, CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER,
		&IID_IVdsServiceLoader, (void **)&pLoader);
	if (hr != S_OK) {
		VDS_SET_ERROR(hr);
		uprintf("Could not create VDS Loader Instance: %s", WindowsErrorString());
		goto out;
	}

	// Load the VDS Service
	hr = IVdsServiceLoader_LoadService(pLoader, L"", &pService);
	IVdsServiceLoader_Release(pLoader);
	if (hr != S_OK) {
		VDS_SET_ERROR(hr);
		uprintf("Could not load VDS Service: %s", WindowsErrorString());
		goto out;
	}

	// Wait for the Service to become ready if needed
	hr = IVdsService_WaitForServiceReady(pService);
	if (hr != S_OK) {
		VDS_SET_ERROR(hr);
		uprintf("VDS Service is not ready: %s", WindowsErrorString());
		goto out;
	}

	// Query the VDS Service Providers
	hr = IVdsService_QueryProviders(pService, VDS_QUERY_SOFTWARE_PROVIDERS, &pEnum);
	if (hr != S_OK) {
		VDS_SET_ERROR(hr);
		uprintf("Could not query VDS Service Providers: %s", WindowsErrorString());
		goto out;
	}

	// Remove mountpoints
	hr = IVdsService_CleanupObsoleteMountPoints(pService);
	if (hr != S_OK) {
		VDS_SET_ERROR(hr);
		uprintf("Could not clean up VDS mountpoints: %s", WindowsErrorString());
		goto out;
	}

	// Invoke layout refresh
	hr = IVdsService_Refresh(pService);
	if (hr != S_OK) {
		VDS_SET_ERROR(hr);
		uprintf("Could not refresh VDS layout: %s", WindowsErrorString());
		goto out;
	}

	// Force re-enum
	hr = IVdsService_Reenumerate(pService);
	if (hr != S_OK) {
		VDS_SET_ERROR(hr);
		uprintf("Could not refresh VDS layout: %s", WindowsErrorString());
		goto out;
	}
	r = TRUE;

	out:
		return r;
}