#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_23__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_27__ {TYPE_5__* DebugInfo; } ;
struct TYPE_30__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_29__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_35__ {scalar_t__ flow; scalar_t__ ref; size_t state; int /*<<< orphan*/  devguid; int /*<<< orphan*/ * drv_id; TYPE_23__ crst; TYPE_4__ IMMEndpoint_iface; TYPE_3__ IMMDevice_iface; } ;
struct TYPE_28__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_26__ {int member_0; int member_1; int member_2; TYPE_2__ member_3; } ;
struct TYPE_34__ {int member_1; TYPE_1__ member_0; } ;
struct TYPE_32__ {int /*<<< orphan*/  ulVal; int /*<<< orphan*/ * pwszVal; } ;
struct TYPE_33__ {scalar_t__ vt; TYPE_6__ u; } ;
struct TYPE_31__ {scalar_t__* Spare; } ;
typedef  TYPE_7__ PROPVARIANT ;
typedef  TYPE_8__ PROPERTYKEY ;
typedef  TYPE_9__ MMDevice ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ EDataFlow ;
typedef  scalar_t__ DWORD_PTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEVPKEY_DeviceInterface_FriendlyName ; 
 int /*<<< orphan*/  DEVPKEY_Device_DeviceDesc ; 
 int /*<<< orphan*/  DEVPKEY_Device_FriendlyName ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_9__** HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__**,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_23__*) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int KEY_READ ; 
 int KEY_WOW64_64KEY ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  MMDeviceVtbl ; 
 int /*<<< orphan*/  MMDevice_GetPropValue (int /*<<< orphan*/ *,scalar_t__,TYPE_8__ const*,TYPE_7__*) ; 
 int /*<<< orphan*/  MMDevice_SetPropValue (int /*<<< orphan*/ *,scalar_t__,TYPE_8__ const*,TYPE_7__*) ; 
 size_t MMDevice_count ; 
 TYPE_9__* MMDevice_def_play ; 
 TYPE_9__* MMDevice_def_rec ; 
 TYPE_9__** MMDevice_head ; 
 int /*<<< orphan*/  MMEndpointVtbl ; 
 int /*<<< orphan*/  Microphone ; 
 TYPE_8__ const PKEY_AudioEndpoint_FormFactor ; 
 TYPE_8__ const PKEY_AudioEndpoint_PhysicalSpeakers ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_7__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_7__*) ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  Speakers ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ VT_LPWSTR ; 
 scalar_t__ VT_UI4 ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ eCapture ; 
 scalar_t__ eRender ; 
 int /*<<< orphan*/  key_capture ; 
 int /*<<< orphan*/  key_render ; 
 int /*<<< orphan*/  reg_devicestate ; 
 int /*<<< orphan*/ * reg_properties ; 
 int /*<<< orphan*/  set_driver_prop_value (int /*<<< orphan*/ *,scalar_t__,TYPE_8__ const*) ; 

__attribute__((used)) static MMDevice *MMDevice_Create(WCHAR *name, GUID *id, EDataFlow flow, DWORD state, BOOL setdefault)
{
    HKEY key, root;
    MMDevice *cur = NULL;
    WCHAR guidstr[39];
    DWORD i;

    static const PROPERTYKEY deviceinterface_key = {
        {0x233164c8, 0x1b2c, 0x4c7d, {0xbc, 0x68, 0xb6, 0x71, 0x68, 0x7a, 0x25, 0x67}}, 1
    };

    static const PROPERTYKEY devicepath_key = {
        {0xb3f8fa53, 0x0004, 0x438e, {0x90, 0x03, 0x51, 0xa4, 0x6e, 0x13, 0x9b, 0xfc}}, 2
    };

    for (i = 0; i < MMDevice_count; ++i)
    {
        MMDevice *device = MMDevice_head[i];
        if (device->flow == flow && IsEqualGUID(&device->devguid, id)){
            cur = device;
            break;
        }
    }

    if(!cur){
        /* No device found, allocate new one */
        cur = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*cur));
        if (!cur)
            return NULL;

        cur->IMMDevice_iface.lpVtbl = &MMDeviceVtbl;
        cur->IMMEndpoint_iface.lpVtbl = &MMEndpointVtbl;

        InitializeCriticalSection(&cur->crst);
        cur->crst.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": MMDevice.crst");

        if (!MMDevice_head)
            MMDevice_head = HeapAlloc(GetProcessHeap(), 0, sizeof(*MMDevice_head));
        else
            MMDevice_head = HeapReAlloc(GetProcessHeap(), 0, MMDevice_head, sizeof(*MMDevice_head)*(1+MMDevice_count));
        MMDevice_head[MMDevice_count++] = cur;
    }else if(cur->ref > 0)
        WARN("Modifying an MMDevice with postitive reference count!\n");

    HeapFree(GetProcessHeap(), 0, cur->drv_id);
    cur->drv_id = name;

    cur->flow = flow;
    cur->state = state;
    cur->devguid = *id;

    StringFromGUID2(&cur->devguid, guidstr, ARRAY_SIZE(guidstr));

    if (flow == eRender)
        root = key_render;
    else
        root = key_capture;

    if (RegCreateKeyExW(root, guidstr, 0, NULL, 0, KEY_WRITE|KEY_READ|KEY_WOW64_64KEY, NULL, &key, NULL) == ERROR_SUCCESS)
    {
        HKEY keyprop;
        RegSetValueExW(key, reg_devicestate, 0, REG_DWORD, (const BYTE*)&state, sizeof(DWORD));
        if (!RegCreateKeyExW(key, reg_properties, 0, NULL, 0, KEY_WRITE|KEY_READ|KEY_WOW64_64KEY, NULL, &keyprop, NULL))
        {
            PROPVARIANT pv;

            pv.vt = VT_LPWSTR;
            pv.u.pwszVal = name;
            MMDevice_SetPropValue(id, flow, (const PROPERTYKEY*)&DEVPKEY_Device_FriendlyName, &pv);
            MMDevice_SetPropValue(id, flow, (const PROPERTYKEY*)&DEVPKEY_DeviceInterface_FriendlyName, &pv);
            MMDevice_SetPropValue(id, flow, (const PROPERTYKEY*)&DEVPKEY_Device_DeviceDesc, &pv);

            pv.u.pwszVal = guidstr;
            MMDevice_SetPropValue(id, flow, &deviceinterface_key, &pv);

            set_driver_prop_value(id, flow, &devicepath_key);

            if (FAILED(set_driver_prop_value(id, flow, &PKEY_AudioEndpoint_FormFactor)))
            {
                pv.vt = VT_UI4;
                pv.u.ulVal = (flow == eCapture) ? Microphone : Speakers;

                MMDevice_SetPropValue(id, flow, &PKEY_AudioEndpoint_FormFactor, &pv);
            }

            if (flow != eCapture)
            {
                PROPVARIANT pv2;

                PropVariantInit(&pv2);

                /* make read-write by not overwriting if already set */
                if (FAILED(MMDevice_GetPropValue(id, flow, &PKEY_AudioEndpoint_PhysicalSpeakers, &pv2)) || pv2.vt != VT_UI4)
                    set_driver_prop_value(id, flow, &PKEY_AudioEndpoint_PhysicalSpeakers);

                PropVariantClear(&pv2);
            }

            RegCloseKey(keyprop);
        }
        RegCloseKey(key);
    }

    if (setdefault)
    {
        if (flow == eRender)
            MMDevice_def_play = cur;
        else
            MMDevice_def_rec = cur;
    }
    return cur;
}