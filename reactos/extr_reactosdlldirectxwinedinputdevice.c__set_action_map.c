#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dps ;
typedef  int /*<<< orphan*/  data_format ;
typedef  char WCHAR ;
struct TYPE_28__ {int dwSize; int dwObjSize; int dwNumObjs; scalar_t__ rgodf; int /*<<< orphan*/  dwDataSize; int /*<<< orphan*/  dwFlags; } ;
struct TYPE_27__ {unsigned int offset; unsigned int dwOfs; int /*<<< orphan*/  uAppData; } ;
struct TYPE_19__ {int dwSize; int dwHeaderSize; void* dwHow; scalar_t__ dwObj; } ;
struct TYPE_26__ {scalar_t__ dwData; TYPE_16__ diph; } ;
struct TYPE_25__ {TYPE_16__ diph; int /*<<< orphan*/  lMax; int /*<<< orphan*/  lMin; } ;
struct TYPE_24__ {char* wsz; TYPE_16__ diph; } ;
struct TYPE_23__ {int num_actions; TYPE_8__* action_map; int /*<<< orphan*/  guid; scalar_t__ acquired; } ;
struct TYPE_22__ {int /*<<< orphan*/  dwObjSize; } ;
struct TYPE_21__ {int dwNumActions; scalar_t__ dwBufferSize; int /*<<< orphan*/  lAxisMax; int /*<<< orphan*/  lAxisMin; TYPE_1__* rgoAction; int /*<<< orphan*/  dwDataSize; } ;
struct TYPE_20__ {int /*<<< orphan*/  uAppData; int /*<<< orphan*/  dwObjID; int /*<<< orphan*/  guidInstance; } ;
typedef  int /*<<< orphan*/  LPDIRECTINPUTDEVICE8W ;
typedef  scalar_t__ LPDIOBJECTDATAFORMAT ;
typedef  TYPE_2__* LPDIACTIONFORMATW ;
typedef  char* LPCWSTR ;
typedef  TYPE_3__* LPCDIDATAFORMAT ;
typedef  TYPE_4__ IDirectInputDeviceImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_5__ DIPROPSTRING ;
typedef  TYPE_6__ DIPROPRANGE ;
typedef  int /*<<< orphan*/  DIPROPHEADER ;
typedef  TYPE_7__ DIPROPDWORD ;
typedef  TYPE_8__ DIOBJECTDATAFORMAT ;
typedef  TYPE_9__ DIDATAFORMAT ;
typedef  int /*<<< orphan*/  ActionMap ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int DIDFT_AXIS ; 
 int DIDFT_BUTTON ; 
 int DIDFT_GETINSTANCE (int /*<<< orphan*/ ) ; 
 int DIDFT_GETTYPE (int /*<<< orphan*/ ) ; 
 int DIDFT_PSHBUTTON ; 
 int DIDFT_RELAXIS ; 
 int /*<<< orphan*/  DIDF_RELAXIS ; 
 int DIDSAM_NOUSER ; 
 int /*<<< orphan*/  DIERR_ACQUIRED ; 
 void* DIPH_DEVICE ; 
 int /*<<< orphan*/  DIPROP_BUFFERSIZE ; 
 int /*<<< orphan*/  DIPROP_RANGE ; 
 int /*<<< orphan*/  DIPROP_USERNAME ; 
 int /*<<< orphan*/  DI_NOEFFECT ; 
 int /*<<< orphan*/  DI_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetUserNameW (char*,int*) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  IDirectInputDevice8_SetDataFormat (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  IDirectInputDevice8_SetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_16__*) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ dataformat_to_odf_by_type (TYPE_3__*,int,int) ; 
 TYPE_4__* impl_from_IDirectInputDevice8W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpynW (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_mapping_settings (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 

HRESULT _set_action_map(LPDIRECTINPUTDEVICE8W iface, LPDIACTIONFORMATW lpdiaf, LPCWSTR lpszUserName, DWORD dwFlags, LPCDIDATAFORMAT df)
{
    IDirectInputDeviceImpl *This = impl_from_IDirectInputDevice8W(iface);
    DIDATAFORMAT data_format;
    DIOBJECTDATAFORMAT *obj_df = NULL;
    DIPROPDWORD dp;
    DIPROPRANGE dpr;
    DIPROPSTRING dps;
    WCHAR username[MAX_PATH];
    DWORD username_size = MAX_PATH;
    int i, action = 0, num_actions = 0;
    unsigned int offset = 0;

    if (This->acquired) return DIERR_ACQUIRED;

    data_format.dwSize = sizeof(data_format);
    data_format.dwObjSize = sizeof(DIOBJECTDATAFORMAT);
    data_format.dwFlags = DIDF_RELAXIS;
    data_format.dwDataSize = lpdiaf->dwDataSize;

    /* Count the actions */
    for (i=0; i < lpdiaf->dwNumActions; i++)
        if (IsEqualGUID(&This->guid, &lpdiaf->rgoAction[i].guidInstance))
            num_actions++;

    if (num_actions == 0) return DI_NOEFFECT;

    This->num_actions = num_actions;

    /* Construct the dataformat and actionmap */
    obj_df = HeapAlloc(GetProcessHeap(), 0, sizeof(DIOBJECTDATAFORMAT)*num_actions);
    data_format.rgodf = (LPDIOBJECTDATAFORMAT)obj_df;
    data_format.dwNumObjs = num_actions;

    HeapFree(GetProcessHeap(), 0, This->action_map);
    This->action_map = HeapAlloc(GetProcessHeap(), 0, sizeof(ActionMap)*num_actions);

    for (i = 0; i < lpdiaf->dwNumActions; i++)
    {
        if (IsEqualGUID(&This->guid, &lpdiaf->rgoAction[i].guidInstance))
        {
            DWORD inst = DIDFT_GETINSTANCE(lpdiaf->rgoAction[i].dwObjID);
            DWORD type = DIDFT_GETTYPE(lpdiaf->rgoAction[i].dwObjID);
            LPDIOBJECTDATAFORMAT obj;

            if (type == DIDFT_PSHBUTTON) type = DIDFT_BUTTON;
            if (type == DIDFT_RELAXIS) type = DIDFT_AXIS;

            obj = dataformat_to_odf_by_type(df, inst, type);

            memcpy(&obj_df[action], obj, df->dwObjSize);

            This->action_map[action].uAppData = lpdiaf->rgoAction[i].uAppData;
            This->action_map[action].offset = offset;
            obj_df[action].dwOfs = offset;
            offset += (type & DIDFT_BUTTON) ? 1 : 4;

            action++;
        }
    }

    IDirectInputDevice8_SetDataFormat(iface, &data_format);

    HeapFree(GetProcessHeap(), 0, obj_df);

    /* Set the device properties according to the action format */
    dpr.diph.dwSize = sizeof(DIPROPRANGE);
    dpr.lMin = lpdiaf->lAxisMin;
    dpr.lMax = lpdiaf->lAxisMax;
    dpr.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dpr.diph.dwHow = DIPH_DEVICE;
    IDirectInputDevice8_SetProperty(iface, DIPROP_RANGE, &dpr.diph);

    if (lpdiaf->dwBufferSize > 0)
    {
        dp.diph.dwSize = sizeof(DIPROPDWORD);
        dp.dwData = lpdiaf->dwBufferSize;
        dp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        dp.diph.dwHow = DIPH_DEVICE;
        IDirectInputDevice8_SetProperty(iface, DIPROP_BUFFERSIZE, &dp.diph);
    }

    /* Retrieve logged user name if necessary */
    if (lpszUserName == NULL)
        GetUserNameW(username, &username_size);
    else
        lstrcpynW(username, lpszUserName, MAX_PATH);

    dps.diph.dwSize = sizeof(dps);
    dps.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dps.diph.dwObj = 0;
    dps.diph.dwHow = DIPH_DEVICE;
    if (dwFlags & DIDSAM_NOUSER)
        dps.wsz[0] = '\0';
    else
        lstrcpynW(dps.wsz, username, ARRAY_SIZE(dps.wsz));
    IDirectInputDevice8_SetProperty(iface, DIPROP_USERNAME, &dps.diph);

    /* Save the settings to disk */
    save_mapping_settings(iface, lpdiaf, username);

    return DI_OK;
}