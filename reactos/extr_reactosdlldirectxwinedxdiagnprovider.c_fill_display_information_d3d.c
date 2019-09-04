#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  driverW ;
typedef  int /*<<< orphan*/  devicenameW ;
typedef  int /*<<< orphan*/  descriptionW ;
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_7__ {int /*<<< orphan*/  LowPart; int /*<<< orphan*/  HighPart; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
struct TYPE_10__ {float VendorId; float DeviceId; float SubSysId; float Revision; int /*<<< orphan*/  DeviceIdentifier; TYPE_2__ DriverVersion; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  Description; int /*<<< orphan*/  Driver; } ;
struct TYPE_9__ {int Width; int Height; int RefreshRate; int /*<<< orphan*/  Format; } ;
typedef  int /*<<< orphan*/  IDxDiagContainerImpl_Container ;
typedef  int /*<<< orphan*/  IDirect3D9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  float DWORD ;
typedef  TYPE_3__ D3DDISPLAYMODE ;
typedef  int /*<<< orphan*/  D3DCAPS9 ;
typedef  TYPE_4__ D3DADAPTER_IDENTIFIER9 ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  D3DDEVTYPE_HAL ; 
 int /*<<< orphan*/  D3D_SDK_VERSION ; 
 int /*<<< orphan*/ * Direct3DCreate9 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int IDirect3D9_GetAdapterCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3D9_GetAdapterDisplayMode (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  IDirect3D9_GetAdapterIdentifier (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  IDirect3D9_GetDeviceCaps (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3D9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  add_bool_property (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  add_bstr_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  add_i4_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_subcontainer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_ui4_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * allocate_information_node (char*) ; 
 char const* bCanRenderWindow ; 
 char const* bDriverBeta ; 
 char const* bDriverDebug ; 
 char const* bDriverSigned ; 
 char const* bDriverSignedValid ; 
 int depth_for_pixelformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwBpp ; 
 int /*<<< orphan*/  dwDDIVersion ; 
 int /*<<< orphan*/  dwHeight ; 
 int /*<<< orphan*/  dwRefreshRate ; 
 int /*<<< orphan*/  dwWHQLLevel ; 
 int /*<<< orphan*/  dwWidth ; 
 int /*<<< orphan*/  get_texture_memory (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  iAdapter ; 
 int /*<<< orphan*/  lDriverSize ; 
 int /*<<< orphan*/  lMiniVddSize ; 
 int /*<<< orphan*/  snprintfW (char*,int,char const*,float,...) ; 
 int /*<<< orphan*/  szChipType ; 
 int /*<<< orphan*/  szDACType ; 
 int /*<<< orphan*/  szDDIVersionEnglish ; 
 int /*<<< orphan*/  szDDIVersionLocalized ; 
 int /*<<< orphan*/  szDescription ; 
 int /*<<< orphan*/  szDeviceId ; 
 int /*<<< orphan*/  szDeviceIdentifier ; 
 int /*<<< orphan*/  szDeviceName ; 
 int /*<<< orphan*/  szDisplayMemoryEnglish ; 
 int /*<<< orphan*/  szDisplayMemoryLocalized ; 
 int /*<<< orphan*/  szDisplayModeEnglish ; 
 int /*<<< orphan*/  szDisplayModeLocalized ; 
 int /*<<< orphan*/  szDriverAttributes ; 
 int /*<<< orphan*/  szDriverDateEnglish ; 
 int /*<<< orphan*/  szDriverDateLocalized ; 
 int /*<<< orphan*/  szDriverLanguageEnglish ; 
 int /*<<< orphan*/  szDriverLanguageLocalized ; 
 int /*<<< orphan*/  szDriverName ; 
 int /*<<< orphan*/  szDriverSignDate ; 
 int /*<<< orphan*/  szDriverVersion ; 
 char const* szEmpty ; 
 int /*<<< orphan*/  szKeyDeviceID ; 
 int /*<<< orphan*/  szKeyDeviceKey ; 
 int /*<<< orphan*/  szManufacturer ; 
 int /*<<< orphan*/  szMiniVdd ; 
 int /*<<< orphan*/  szMiniVddDateEnglish ; 
 int /*<<< orphan*/  szMiniVddDateLocalized ; 
 int /*<<< orphan*/  szMonitorMaxRes ; 
 int /*<<< orphan*/  szMonitorName ; 
 int /*<<< orphan*/  szRevision ; 
 int /*<<< orphan*/  szRevisionId ; 
 int /*<<< orphan*/  szSubSysId ; 
 int /*<<< orphan*/  szVdd ; 
 int /*<<< orphan*/  szVendorId ; 
 char const* vendor_id_to_manufacturer_string (float) ; 

__attribute__((used)) static HRESULT fill_display_information_d3d(IDxDiagContainerImpl_Container *node)
{
    IDxDiagContainerImpl_Container *display_adapter;
    HRESULT hr;
    IDirect3D9 *pDirect3D9;
    WCHAR buffer[256];
    UINT index, count;

    pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pDirect3D9)
        return E_FAIL;

    count = IDirect3D9_GetAdapterCount(pDirect3D9);
    for (index = 0; index < count; index++)
    {
        static const WCHAR adapterid_fmtW[] = {'%','u',0};
        static const WCHAR driverversion_fmtW[] = {'%','u','.','%','u','.','%','0','4','u','.','%','0','4','u',0};
        static const WCHAR id_fmtW[] = {'0','x','%','0','4','x',0};
        static const WCHAR subsysid_fmtW[] = {'0','x','%','0','8','x',0};
        static const WCHAR mem_fmt[] = {'%','.','1','f',' ','M','B',0};
        static const WCHAR b3DAccelerationExists[] = {'b','3','D','A','c','c','e','l','e','r','a','t','i','o','n','E','x','i','s','t','s',0};
        static const WCHAR b3DAccelerationEnabled[] = {'b','3','D','A','c','c','e','l','e','r','a','t','i','o','n','E','n','a','b','l','e','d',0};
        static const WCHAR bDDAccelerationEnabled[] = {'b','D','D','A','c','c','e','l','e','r','a','t','i','o','n','E','n','a','b','l','e','d',0};
        static const WCHAR bNoHardware[] = {'b','N','o','H','a','r','d','w','a','r','e',0};
        static const WCHAR mode_fmtW[] = {'%','d',' ','x',' ','%','d',' ','(','%','d',' ','b','i','t',')',' ','(','%','d','H','z',')',0};
        static const WCHAR gernericPNPMonitorW[] = {'G','e','n','e','r','i','c',' ','P','n','P',' ','M','o','n','i','t','o','r',0};
        static const WCHAR failedToGetParameterW[] = {'F','a','i','l','e','d',' ','t','o',' ','g','e','t',' ','p','a','r','a','m','e','t','e','r',0};
        static const WCHAR driverAttributesW[] = {'F','i','n','a','l',' ','R','e','t','a','i','l',0};
        static const WCHAR englishW[] = {'E','n','g','l','i','s','h',0};
        static const WCHAR driverDateEnglishW[] = {'1','/','1','/','2','0','1','6',' ','1','0',':','0','0',':','0','0',0};
        static const WCHAR driverDateLocalW[] = {'1','/','1','/','2','0','1','6',' ','1','0',':','0','0',':','0','0',' ','A','M',0};
        static const WCHAR naW[] = {'n','/','a',0};
        static const WCHAR ddi11W[] = {'1','1',0};

        D3DADAPTER_IDENTIFIER9 adapter_info;
        D3DDISPLAYMODE adapter_mode;
        D3DCAPS9 device_caps;
        DWORD available_mem = 0;
        BOOL hardware_accel;

        snprintfW(buffer, sizeof(buffer)/sizeof(WCHAR), adapterid_fmtW, index);
        display_adapter = allocate_information_node(buffer);
        if (!display_adapter)
        {
            hr = E_OUTOFMEMORY;
            goto cleanup;
        }

        add_subcontainer(node, display_adapter);

        hr = IDirect3D9_GetAdapterIdentifier(pDirect3D9, index, 0, &adapter_info);
        if (SUCCEEDED(hr))
        {
            WCHAR driverW[sizeof(adapter_info.Driver)];
            WCHAR descriptionW[sizeof(adapter_info.Description)];
            WCHAR devicenameW[sizeof(adapter_info.DeviceName)];

            MultiByteToWideChar(CP_ACP, 0, adapter_info.Driver, -1, driverW, sizeof(driverW)/sizeof(WCHAR));
            MultiByteToWideChar(CP_ACP, 0, adapter_info.Description, -1, descriptionW, sizeof(descriptionW)/sizeof(WCHAR));
            MultiByteToWideChar(CP_ACP, 0, adapter_info.DeviceName, -1, devicenameW, sizeof(devicenameW)/sizeof(WCHAR));

            hr = add_bstr_property(display_adapter, szDriverName, driverW);
            if (FAILED(hr))
                goto cleanup;

            hr = add_bstr_property(display_adapter, szDescription, descriptionW);
            if (FAILED(hr))
                goto cleanup;

            hr = add_bstr_property(display_adapter, szDeviceName, devicenameW);
            if (FAILED(hr))
                goto cleanup;

            snprintfW(buffer, sizeof(buffer)/sizeof(WCHAR), driverversion_fmtW,
                      HIWORD(adapter_info.DriverVersion.u.HighPart), LOWORD(adapter_info.DriverVersion.u.HighPart),
                      HIWORD(adapter_info.DriverVersion.u.LowPart), LOWORD(adapter_info.DriverVersion.u.LowPart));

            hr = add_bstr_property(display_adapter, szDriverVersion, buffer);
            if (FAILED(hr))
                goto cleanup;

            snprintfW(buffer, sizeof(buffer)/sizeof(WCHAR), id_fmtW, adapter_info.VendorId);
            hr = add_bstr_property(display_adapter, szVendorId, buffer);
            if (FAILED(hr))
                goto cleanup;

            snprintfW(buffer, sizeof(buffer)/sizeof(WCHAR), id_fmtW, adapter_info.DeviceId);
            hr = add_bstr_property(display_adapter, szDeviceId, buffer);
            if (FAILED(hr))
                goto cleanup;

            snprintfW(buffer, sizeof(buffer)/sizeof(WCHAR), subsysid_fmtW, adapter_info.SubSysId);
            hr = add_bstr_property(display_adapter, szSubSysId, buffer);
            if (FAILED(hr))
                goto cleanup;

            snprintfW(buffer, sizeof(buffer)/sizeof(WCHAR), id_fmtW, adapter_info.Revision);
            hr = add_bstr_property(display_adapter, szRevisionId, buffer);
            if (FAILED(hr))
                goto cleanup;

            StringFromGUID2(&adapter_info.DeviceIdentifier, buffer, 39);
            hr = add_bstr_property(display_adapter, szDeviceIdentifier, buffer);
            if (FAILED(hr))
                goto cleanup;

            hr = add_bstr_property(display_adapter, szManufacturer, vendor_id_to_manufacturer_string(adapter_info.VendorId));
            if (FAILED(hr))
                goto cleanup;
        }

        hr = IDirect3D9_GetAdapterDisplayMode(pDirect3D9, index, &adapter_mode);
        if (SUCCEEDED(hr))
        {
            hr = add_ui4_property(display_adapter, dwWidth, adapter_mode.Width);
            if (FAILED(hr))
                goto cleanup;

            hr = add_ui4_property(display_adapter, dwHeight, adapter_mode.Height);
            if (FAILED(hr))
                goto cleanup;

            hr = add_ui4_property(display_adapter, dwRefreshRate, adapter_mode.RefreshRate);
            if (FAILED(hr))
                goto cleanup;

            hr = add_ui4_property(display_adapter, dwBpp, depth_for_pixelformat(adapter_mode.Format));
            if (FAILED(hr))
                goto cleanup;

            snprintfW(buffer, sizeof(buffer)/sizeof(WCHAR), mode_fmtW, adapter_mode.Width, adapter_mode.Height,
                      depth_for_pixelformat(adapter_mode.Format), adapter_mode.RefreshRate);

            hr = add_bstr_property(display_adapter, szDisplayModeLocalized, buffer);
            if (FAILED(hr))
                goto cleanup;

            hr = add_bstr_property(display_adapter, szDisplayModeEnglish, buffer);
            if (FAILED(hr))
                goto cleanup;
        }

        hr = add_bstr_property(display_adapter, szKeyDeviceKey, szEmpty);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szKeyDeviceID, szEmpty);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szChipType, szEmpty);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDACType, szEmpty);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szRevision, szEmpty);
        if (FAILED(hr))
            goto cleanup;

        if (!get_texture_memory(&adapter_info.DeviceIdentifier, &available_mem))
            WARN("get_texture_memory helper failed\n");

        snprintfW(buffer, sizeof(buffer)/sizeof(buffer[0]), mem_fmt, available_mem / 1000000.0f);

        hr = add_bstr_property(display_adapter, szDisplayMemoryLocalized, buffer);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDisplayMemoryEnglish, buffer);
        if (FAILED(hr))
            goto cleanup;

        hr = IDirect3D9_GetDeviceCaps(pDirect3D9, index, D3DDEVTYPE_HAL, &device_caps);
        hardware_accel = SUCCEEDED(hr);

        hr = add_bool_property(display_adapter, b3DAccelerationEnabled, hardware_accel);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bool_property(display_adapter, b3DAccelerationExists, hardware_accel);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bool_property(display_adapter, bDDAccelerationEnabled, hardware_accel);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bool_property(display_adapter, bNoHardware, FALSE);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bool_property(display_adapter, bCanRenderWindow, TRUE);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szMonitorName, gernericPNPMonitorW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szMonitorMaxRes, failedToGetParameterW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDriverAttributes, driverAttributesW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDriverLanguageEnglish, englishW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDriverLanguageLocalized, englishW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDriverDateEnglish, driverDateEnglishW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDriverDateLocalized, driverDateLocalW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_i4_property(display_adapter, lDriverSize, 10 * 1024 * 1024);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szMiniVdd, naW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szMiniVddDateLocalized, naW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szMiniVddDateEnglish, naW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_i4_property(display_adapter, lMiniVddSize, 0);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szVdd, naW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bool_property(display_adapter, bDriverBeta, FALSE);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bool_property(display_adapter, bDriverDebug, FALSE);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bool_property(display_adapter, bDriverSigned, TRUE);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bool_property(display_adapter, bDriverSignedValid, TRUE);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDriverSignDate, naW);
        if (FAILED(hr))
            goto cleanup;

        hr = add_ui4_property(display_adapter, dwDDIVersion, 11);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDDIVersionEnglish, ddi11W);
        if (FAILED(hr))
            goto cleanup;

        hr = add_bstr_property(display_adapter, szDDIVersionLocalized, ddi11W);
        if (FAILED(hr))
            goto cleanup;

        hr = add_ui4_property(display_adapter, iAdapter, index);
        if (FAILED(hr))
            goto cleanup;

        hr = add_ui4_property(display_adapter, dwWHQLLevel, 0);
        if (FAILED(hr))
            goto cleanup;
    }

    hr = S_OK;
cleanup:
    IDirect3D9_Release(pDirect3D9);
    return hr;
}