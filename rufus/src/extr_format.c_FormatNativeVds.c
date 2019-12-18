#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * pwszName; } ;
typedef  TYPE_1__ VDS_VOLUME_PROP ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  IVdsVolumeMF3 ;
typedef  int /*<<< orphan*/  IVdsVolume ;
typedef  int /*<<< orphan*/  IVdsSwProvider ;
typedef  int /*<<< orphan*/  IVdsServiceLoader ;
typedef  int /*<<< orphan*/  IVdsService ;
typedef  int /*<<< orphan*/  IVdsProvider ;
typedef  int /*<<< orphan*/  IVdsPack ;
typedef  int /*<<< orphan*/  IVdsAsync ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IEnumVdsObject ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_USER_CANCEL ; 
 int CLSCTX_LOCAL_SERVER ; 
 int CLSCTX_REMOTE_SERVER ; 
 int /*<<< orphan*/  CLSID_VdsLoader ; 
 int /*<<< orphan*/  COINIT_APARTMENTTHREADED ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoInitializeSecurity (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int ERROR_GEN_FAILURE ; 
 int ERROR_PATH_NOT_FOUND ; 
 int ERROR_SEVERITY_ERROR ; 
 scalar_t__ E_FAIL ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int FALSE ; 
 int FP_COMPRESSION ; 
 int FP_QUICK ; 
 size_t FS_EXFAT ; 
 size_t FS_UDF ; 
 int /*<<< orphan*/ * FileSystemLabel ; 
 int FormatStatus ; 
 char* GetLogicalName (int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ IEnumVdsObject_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IVdsPack ; 
 int /*<<< orphan*/  IID_IVdsProvider ; 
 int /*<<< orphan*/  IID_IVdsServiceLoader ; 
 int /*<<< orphan*/  IID_IVdsSwProvider ; 
 int /*<<< orphan*/  IID_IVdsVolume ; 
 int /*<<< orphan*/  IID_IVdsVolumeMF3 ; 
 scalar_t__ IS_ERROR (int) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IVdsAsync_Cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsAsync_QueryStatus (int /*<<< orphan*/ *,scalar_t__*,int*) ; 
 int /*<<< orphan*/  IVdsAsync_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsPack_QueryVolumes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IVdsProvider_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsServiceLoader_LoadService (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IVdsServiceLoader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsService_QueryProviders (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IVdsService_WaitForServiceReady (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsSwProvider_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IVdsSwProvider_QueryPacks (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IVdsSwProvider_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsVolumeMF3_FormatEx2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ **) ; 
 scalar_t__ IVdsVolumeMF3_QueryVolumeGuidPathnames (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  IVdsVolumeMF3_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVdsVolume_GetProperties (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ IVdsVolume_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IVdsVolume_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_217 ; 
 int /*<<< orphan*/  MSG_218 ; 
 int /*<<< orphan*/  MSG_220 ; 
 int /*<<< orphan*/  MSG_222 ; 
 int /*<<< orphan*/  OP_CREATE_FS ; 
 int /*<<< orphan*/  OP_FORMAT ; 
 int /*<<< orphan*/  PrintInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PrintInfoDebug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  RPC_C_AUTHN_LEVEL_CONNECT ; 
 int /*<<< orphan*/  RPC_C_IMP_LEVEL_IMPERSONATE ; 
 int /*<<< orphan*/  ReadSetting32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETTING_USE_UDF_VERSION ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int TRUE ; 
 int /*<<< orphan*/  UpdateProgress (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  UpdateProgressWithInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UpdateProgressWithInfoInit (int /*<<< orphan*/ *,int) ; 
 scalar_t__ VDS_E_OPERATION_PENDING ; 
 int /*<<< orphan*/  VDS_QUERY_SOFTWARE_PROVIDERS ; 
 int /*<<< orphan*/  VDS_SET_ERROR (scalar_t__) ; 
 scalar_t__ VDS_S_PROPERTIES_INCOMPLETE ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 scalar_t__ dur_mins ; 
 scalar_t__ dur_secs ; 
 float format_percent ; 
 int /*<<< orphan*/  safe_free (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 
 char* utf8_to_wchar (char*) ; 
 scalar_t__ wcscmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL FormatNativeVds(DWORD DriveIndex, uint64_t PartitionOffset, DWORD ClusterSize, LPCSTR FSName, LPCSTR Label, DWORD Flags)
{
	BOOL r = FALSE, bFoundVolume = FALSE;
	HRESULT hr;
	ULONG ulFetched;
	IVdsServiceLoader *pLoader;
	IVdsService *pService;
	IEnumVdsObject *pEnum;
	IUnknown *pUnk;
	char* VolumeName = NULL;
	WCHAR *wVolumeName = NULL, *wLabel = utf8_to_wchar(Label), *wFSName = utf8_to_wchar(FSName);

	if ((strcmp(FSName, FileSystemLabel[FS_EXFAT]) == 0) && !((dur_mins == 0) && (dur_secs == 0))) {
		PrintInfoDebug(0, MSG_220, FSName, dur_mins, dur_secs);
	} else {
		PrintInfoDebug(0, MSG_222, FSName);
	}
	UpdateProgressWithInfoInit(NULL, TRUE);
	VolumeName = GetLogicalName(DriveIndex, PartitionOffset, TRUE, TRUE);
	wVolumeName = utf8_to_wchar(VolumeName);
	if (wVolumeName == NULL) {
		uprintf("Could not read volume name");
		FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | ERROR_GEN_FAILURE;
		goto out;
	}

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
		CHECK_FOR_USER_CANCEL;

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
			IEnumVdsObject *pEnumVolume;
			IUnknown *pVolumeUnk;
			CHECK_FOR_USER_CANCEL;

			hr = IUnknown_QueryInterface(pPackUnk, &IID_IVdsPack, (void **)&pPack);
			IUnknown_Release(pPackUnk);
			if (hr != S_OK) {
				VDS_SET_ERROR(hr);
				uprintf("Could not query VDS Software Provider Pack: %s", WindowsErrorString());
				goto out;
			}

			// Use the pack interface to access the volumes
			hr = IVdsPack_QueryVolumes(pPack, &pEnumVolume);
			if (hr != S_OK) {
				VDS_SET_ERROR(hr);
				uprintf("Could not query VDS volumes: %s", WindowsErrorString());
				goto out;
			}

			// List volumes
			while (IEnumVdsObject_Next(pEnumVolume, 1, &pVolumeUnk, &ulFetched) == S_OK) {
				BOOL match;
				HRESULT hr2 = E_FAIL;
				VDS_VOLUME_PROP VolumeProps;
				LPWSTR *wszPathArray;
				ULONG ulPercentCompleted, ulNumberOfPaths;
				USHORT usFsVersion = 0;
				IVdsVolume *pVolume;
				IVdsAsync* pAsync;
				IVdsVolumeMF3 *pVolumeMF3;
				CHECK_FOR_USER_CANCEL;

				// Get the volume interface.
				hr = IUnknown_QueryInterface(pVolumeUnk, &IID_IVdsVolume, (void **)&pVolume);
				if (hr != S_OK) {
					VDS_SET_ERROR(hr);
					uprintf("Could not query VDS Volume Interface: %s", WindowsErrorString());
					goto out;
				}

				hr = IVdsVolume_GetProperties(pVolume, &VolumeProps);
				if ((hr != S_OK) && (hr != VDS_S_PROPERTIES_INCOMPLETE)) {
					VDS_SET_ERROR(hr);
					IVdsVolume_Release(pVolume);
					uprintf("Could not query VDS Volume Properties: %s", WindowsErrorString());
					continue;
				}
				CoTaskMemFree(VolumeProps.pwszName);

				// Instantiate the IVdsVolumeMF3 interface for our volume.
				hr = IVdsVolume_QueryInterface(pVolume, &IID_IVdsVolumeMF3, (void **)&pVolumeMF3);
				IVdsVolume_Release(pVolume);
				if (hr != S_OK) {
					VDS_SET_ERROR(hr);
					uprintf("Could not access VDS VolumeMF3 interface: %s", WindowsErrorString());
					continue;
				}

				// Query the volume GUID
				hr = IVdsVolumeMF3_QueryVolumeGuidPathnames(pVolumeMF3, &wszPathArray, &ulNumberOfPaths);
				if (hr != S_OK) {
					VDS_SET_ERROR(hr);
					uprintf("Could not query VDS VolumeGuidPathnames: %s", WindowsErrorString());
					continue;
				}

				if (ulNumberOfPaths > 1)
					uprintf("Notice: Volume %S has more than one GUID...", wszPathArray[0]);

				match = (wcscmp(wVolumeName, wszPathArray[0]) == 0);
				CoTaskMemFree(wszPathArray);
				if (!match)
					continue;

				bFoundVolume = TRUE;
				if (strcmp(Label, FileSystemLabel[FS_UDF]) == 0)
					usFsVersion = ReadSetting32(SETTING_USE_UDF_VERSION);
				if (ClusterSize < 0x200) {
					ClusterSize = 0;
					uprintf("Using default cluster size");
				} else {
					uprintf("Using cluster size: %d bytes", ClusterSize);
				}
				format_percent = 0.0f;
				uprintf("%s format was selected", (Flags & FP_QUICK) ? "Quick" : "Slow");
				if (Flags & FP_COMPRESSION)
					uprintf("NTFS compression is enabled");

				hr = IVdsVolumeMF3_FormatEx2(pVolumeMF3, wFSName, usFsVersion, ClusterSize, wLabel, Flags, &pAsync);
				while (SUCCEEDED(hr)) {
					if (IS_ERROR(FormatStatus)) {
						IVdsAsync_Cancel(pAsync);
						break;
					}
					hr = IVdsAsync_QueryStatus(pAsync, &hr2, &ulPercentCompleted);
					if (SUCCEEDED(hr)) {
						if (Flags & FP_QUICK) {
							// Progress report on quick format is useless, so we'll just pretend we have 2 tasks
							PrintInfo(0, MSG_218, (ulPercentCompleted < 100) ? 1 : 2, 2);
							UpdateProgress(OP_CREATE_FS, (float)ulPercentCompleted);
						} else {
							UpdateProgressWithInfo(OP_FORMAT, MSG_217, ulPercentCompleted, 100);
						}
						hr = hr2;
						if (hr == S_OK)
							break;
						if (hr == VDS_E_OPERATION_PENDING)
							hr = S_OK;
					}
					Sleep(500);
				}
				if (!SUCCEEDED(hr)) {
					VDS_SET_ERROR(hr);
					uprintf("Could not format drive: %s", WindowsErrorString());
					goto out;
				}

				IVdsAsync_Release(pAsync);
				IVdsVolumeMF3_Release(pVolumeMF3);

				if (!IS_ERROR(FormatStatus)) {
					uprintf("Format completed.");
					r = TRUE;
				}
				goto out;
			}
		}
	}

out:
	if ((!bFoundVolume) && (FormatStatus == 0))
		FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | ERROR_PATH_NOT_FOUND;
	safe_free(VolumeName);
	safe_free(wVolumeName);
	safe_free(wLabel);
	safe_free(wFSName);
	return r;
}