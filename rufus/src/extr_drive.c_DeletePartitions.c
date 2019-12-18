#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_6__ {int /*<<< orphan*/  ullOffset; int /*<<< orphan*/  ullSize; int /*<<< orphan*/  ulPartitionNumber; } ;
typedef  TYPE_1__ VDS_PARTITION_PROP ;
struct TYPE_7__ {int /*<<< orphan*/  pwszName; } ;
typedef  TYPE_2__ VDS_DISK_PROP ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  size_t LONG ;
typedef  int /*<<< orphan*/  IVdsSwProvider ;
typedef  int /*<<< orphan*/  IVdsServiceLoader ;
typedef  int /*<<< orphan*/  IVdsService ;
typedef  int /*<<< orphan*/  IVdsProvider ;
typedef  int /*<<< orphan*/  IVdsPack ;
typedef  int /*<<< orphan*/  IVdsDisk ;
typedef  int /*<<< orphan*/  IVdsAsync ;
typedef  int /*<<< orphan*/  IVdsAdvancedDisk ;
typedef  int /*<<< orphan*/  IUnknown ;
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
 int /*<<< orphan*/  CoTaskMemFree (TYPE_1__*) ; 
 scalar_t__ E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FormatStatus ; 
 scalar_t__ IEnumVdsObject_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IVdsAdvancedDisk ; 
 int /*<<< orphan*/  IID_IVdsDisk ; 
 int /*<<< orphan*/  IID_IVdsPack ; 
 int /*<<< orphan*/  IID_IVdsProvider ; 
 int /*<<< orphan*/  IID_IVdsServiceLoader ; 
 int /*<<< orphan*/  IID_IVdsSwProvider ; 
 scalar_t__ IS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsAdvancedDisk_Clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IVdsAdvancedDisk_DeletePartition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IVdsAdvancedDisk_QueryPartitions (int /*<<< orphan*/ *,TYPE_1__**,size_t*) ; 
 int /*<<< orphan*/  IVdsAdvancedDisk_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IVdsAsync_Cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsAsync_QueryStatus (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsDisk_GetProperties (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ IVdsDisk_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IVdsDisk_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsPack_QueryDisks (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IVdsProvider_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsServiceLoader_LoadService (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IVdsServiceLoader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsService_QueryProviders (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IVdsService_WaitForServiceReady (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsSwProvider_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IVdsSwProvider_QueryPacks (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IVdsSwProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_C_AUTHN_LEVEL_CONNECT ; 
 int /*<<< orphan*/  RPC_C_IMP_LEVEL_IMPERSONATE ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SizeToHumanReadable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VDS_E_OPERATION_PENDING ; 
 int /*<<< orphan*/  VDS_QUERY_SOFTWARE_PROVIDERS ; 
 int /*<<< orphan*/  VDS_SET_ERROR (scalar_t__) ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wnsprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

BOOL DeletePartitions(DWORD DriveIndex)
{
	BOOL r = FALSE;
	HRESULT hr;
	ULONG ulFetched;
	wchar_t wPhysicalName[24];
	IVdsServiceLoader *pLoader;
	IVdsService *pService;
	IEnumVdsObject *pEnum;
	IUnknown *pUnk;

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

	while (IEnumVdsObject_Next(pEnum, 1, &pUnk, &ulFetched) == S_OK) {
		IVdsProvider *pProvider;
		IVdsSwProvider *pSwProvider;
		IEnumVdsObject *pEnumPack;
		IUnknown *pPackUnk;

		// Get VDS Provider
		hr = IUnknown_QueryInterface(pUnk, &IID_IVdsProvider, (void **)&pProvider);
		IUnknown_Release(pUnk);
		if (hr != S_OK) {
			VDS_SET_ERROR(hr);
			uprintf("Could not get VDS Provider: %s", WindowsErrorString());
			goto out;
		}

		// Get VDS Software Provider
		hr = IVdsSwProvider_QueryInterface(pProvider, &IID_IVdsSwProvider, (void **)&pSwProvider);
		IVdsProvider_Release(pProvider);
		if (hr != S_OK) {
			VDS_SET_ERROR(hr);
			uprintf("Could not get VDS Software Provider: %s", WindowsErrorString());
			goto out;
		}

		// Get VDS Software Provider Packs
		hr = IVdsSwProvider_QueryPacks(pSwProvider, &pEnumPack);
		IVdsSwProvider_Release(pSwProvider);
		if (hr != S_OK) {
			VDS_SET_ERROR(hr);
			uprintf("Could not get VDS Software Provider Packs: %s", WindowsErrorString());
			goto out;
		}

		// Enumerate Provider Packs
		while (IEnumVdsObject_Next(pEnumPack, 1, &pPackUnk, &ulFetched) == S_OK) {
			IVdsPack *pPack;
			IEnumVdsObject *pEnumDisk;
			IUnknown *pDiskUnk;

			hr = IUnknown_QueryInterface(pPackUnk, &IID_IVdsPack, (void **)&pPack);
			IUnknown_Release(pPackUnk);
			if (hr != S_OK) {
				VDS_SET_ERROR(hr);
				uprintf("Could not query VDS Software Provider Pack: %s", WindowsErrorString());
				goto out;
			}

			// Use the pack interface to access the disks
			hr = IVdsPack_QueryDisks(pPack, &pEnumDisk);
			if (hr != S_OK) {
				VDS_SET_ERROR(hr);
				uprintf("Could not query VDS disks: %s", WindowsErrorString());
				goto out;
			}

			// List disks
			while (IEnumVdsObject_Next(pEnumDisk, 1, &pDiskUnk, &ulFetched) == S_OK) {
				VDS_DISK_PROP diskprop;
				VDS_PARTITION_PROP* prop_array;
				LONG i, prop_array_size;
				IVdsDisk *pDisk;
				IVdsAdvancedDisk *pAdvancedDisk;

				// Get the disk interface.
				hr = IUnknown_QueryInterface(pDiskUnk, &IID_IVdsDisk, (void **)&pDisk);
				if (hr != S_OK) {
					VDS_SET_ERROR(hr);
					uprintf("Could not query VDS Disk Interface: %s", WindowsErrorString());
					goto out;
				}

				// Get the disk properties
				hr = IVdsDisk_GetProperties(pDisk, &diskprop);
				if (hr != S_OK) {
					VDS_SET_ERROR(hr);
					uprintf("Could not query VDS Disk Properties: %s", WindowsErrorString());
					goto out;
				}

				// Isolate the disk we want
				if (_wcsicmp(wPhysicalName, diskprop.pwszName) != 0) {
					IVdsDisk_Release(pDisk);
					continue;
				}

				// Instantiate the AdvanceDisk interface for our disk.
				hr = IVdsDisk_QueryInterface(pDisk, &IID_IVdsAdvancedDisk, (void **)&pAdvancedDisk);
				IVdsDisk_Release(pDisk);
				if (hr != S_OK) {
					VDS_SET_ERROR(hr);
					uprintf("Could not access VDS Advanced Disk interface: %s", WindowsErrorString());
					goto out;
				}

				// Query the partition data, so we can get the start offset, which we need for deletion
				hr = IVdsAdvancedDisk_QueryPartitions(pAdvancedDisk, &prop_array, &prop_array_size);
				if (hr == S_OK) {
					uprintf("Deleting ALL partition(s) from disk '%S':", diskprop.pwszName);
					// Now go through each partition
					for (i = 0; i < prop_array_size; i++) {
						uprintf("● Partition %d (offset: %lld, size: %s)", prop_array[i].ulPartitionNumber,
							prop_array[i].ullOffset, SizeToHumanReadable(prop_array[i].ullSize, FALSE, FALSE));
						hr = IVdsAdvancedDisk_DeletePartition(pAdvancedDisk, prop_array[i].ullOffset, TRUE, TRUE);
						if (hr != S_OK) {
							r = FALSE;
							VDS_SET_ERROR(hr);
							uprintf("Could not delete partitions: %s", WindowsErrorString());
						}
					}
					r = TRUE;
				} else {
					uprintf("No partition to delete on disk '%S'", diskprop.pwszName);
					r = TRUE;
				}
				CoTaskMemFree(prop_array);

#if 0
				// Issue a Clean while we're at it
				HRESULT hr2 = E_FAIL;
				ULONG completed;
				IVdsAsync* pAsync;
				hr = IVdsAdvancedDisk_Clean(pAdvancedDisk, TRUE, FALSE, FALSE, &pAsync);
				while (SUCCEEDED(hr)) {
					if (IS_ERROR(FormatStatus)) {
						IVdsAsync_Cancel(pAsync);
						break;
					}
					hr = IVdsAsync_QueryStatus(pAsync, &hr2, &completed);
					if (SUCCEEDED(hr)) {
						hr = hr2;
						if (hr == S_OK)
							break;
						if (hr == VDS_E_OPERATION_PENDING)
							hr = S_OK;
					}
					Sleep(500);
				}
				if (hr != S_OK) {
					VDS_SET_ERROR(hr);
					uprintf("Could not clean disk: %s", WindowsErrorString());
				}
#endif
				IVdsAdvancedDisk_Release(pAdvancedDisk);
				goto out;
			}
		}
	}

out:
	return r;
}