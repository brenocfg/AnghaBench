#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct TYPE_11__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_12__ {char* requested_device; char* acquired_device; float requested_volume; float gain; scalar_t__ requested_mute; int /*<<< orphan*/ * dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  session_events; int /*<<< orphan*/  duck; int /*<<< orphan*/  work; int /*<<< orphan*/  ready; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/ * LPCGUID ;
typedef  int /*<<< orphan*/  ISimpleAudioVolume ;
typedef  int /*<<< orphan*/  IMMDeviceEnumerator ;
typedef  int /*<<< orphan*/  IAudioSessionManager2 ;
typedef  int /*<<< orphan*/  IAudioSessionManager ;
typedef  int /*<<< orphan*/  IAudioSessionControl2 ;
typedef  int /*<<< orphan*/  IAudioSessionControl ;
typedef  int /*<<< orphan*/  IAudioEndpointVolume ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_E_DEVICE_INVALIDATED ; 
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 char* FromWide (char*) ; 
 int /*<<< orphan*/  GUID_VLC_AUD_OUT ; 
 int /*<<< orphan*/  IAudioEndpointVolume_GetVolumeRange (int /*<<< orphan*/ *,float*,float*,float*) ; 
 int /*<<< orphan*/  IAudioEndpointVolume_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionControl2_GetSessionInstanceIdentifier (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  IAudioSessionControl2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionControl2_SetDuckingPreference (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IAudioSessionControl_RegisterAudioSessionNotification (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionControl_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionControl_SetDisplayName (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionControl_UnregisterAudioSessionNotification (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionManager2_RegisterDuckNotification (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionManager2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionManager2_UnregisterDuckNotification (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioSessionManager_GetAudioSessionControl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IAudioSessionManager_GetSimpleAudioVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IAudioSessionManager_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAudioSessionManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioEndpointVolume ; 
 int /*<<< orphan*/  IID_IAudioSessionControl2 ; 
 int /*<<< orphan*/  IID_IAudioSessionManager ; 
 int /*<<< orphan*/  IID_IAudioSessionManager2 ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_GetDefaultAudioEndpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_GetDevice (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMMDevice_Activate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMMDevice_GetId (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  IMMDevice_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ISimpleAudioVolume_GetMasterVolume (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_GetMute (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_SetMasterVolume (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_SetMute (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SleepConditionVariableCS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 char* ToWide (char*) ; 
 int /*<<< orphan*/  WakeConditionVariable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_DeviceReport (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  aout_MuteReport (TYPE_1__*,int) ; 
 int /*<<< orphan*/  aout_VolumeReport (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbrtf (float) ; 
 char* default_device ; 
 char* default_device_b ; 
 int /*<<< orphan*/  eConsole ; 
 int /*<<< orphan*/  eRender ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*,...) ; 
 scalar_t__ var_GetBool (TYPE_1__*,char*) ; 
 char* var_InheritString (TYPE_1__*,char*) ; 

__attribute__((used)) static HRESULT MMSession(audio_output_t *aout, IMMDeviceEnumerator *it)
{
    aout_sys_t *sys = aout->sys;
    IAudioSessionManager *manager;
    IAudioSessionControl *control;
    ISimpleAudioVolume *volume;
    IAudioEndpointVolume *endpoint;
    void *pv;
    HRESULT hr;

    assert(sys->requested_device != NULL);
    assert(sys->dev == NULL);

    /* Yes, it's perfectly valid to request the same device, see Start()
     * comments. */
    if (sys->acquired_device != sys->requested_device
     && sys->acquired_device != default_device)
        free(sys->acquired_device);
    if (sys->requested_device != default_device) /* Device selected explicitly */
    {
        msg_Dbg(aout, "using selected device %ls", sys->requested_device);
        hr = IMMDeviceEnumerator_GetDevice(it, sys->requested_device, &sys->dev);
        if (FAILED(hr))
            msg_Err(aout, "cannot get selected device %ls (error 0x%lX)",
                    sys->requested_device, hr);
        sys->acquired_device = sys->requested_device;
    }
    else
        hr = AUDCLNT_E_DEVICE_INVALIDATED;

    while (hr == AUDCLNT_E_DEVICE_INVALIDATED)
    {   /* Default device selected by policy and with stream routing.
         * "Do not use eMultimedia" says MSDN. */
        msg_Dbg(aout, "using default device");
        hr = IMMDeviceEnumerator_GetDefaultAudioEndpoint(it, eRender,
                                                         eConsole, &sys->dev);
        if (FAILED(hr))
        {
            msg_Err(aout, "cannot get default device (error 0x%lX)", hr);
            sys->acquired_device = NULL;
        }
        else
            sys->acquired_device = default_device;
    }

    sys->requested_device = NULL;
    WakeConditionVariable(&sys->ready);

    if (SUCCEEDED(hr))
    {   /* Report actual device */
        LPWSTR wdevid;

        if (sys->acquired_device == default_device)
            aout_DeviceReport(aout, default_device_b);
        else
        {
            hr = IMMDevice_GetId(sys->dev, &wdevid);
            if (SUCCEEDED(hr))
            {
                char *id = FromWide(wdevid);
                CoTaskMemFree(wdevid);
                if (likely(id != NULL))
                {
                    aout_DeviceReport(aout, id);
                    free(id);
                }
            }
        }
    }
    else
    {
        msg_Err(aout, "cannot get device identifier (error 0x%lX)", hr);
        return hr;
    }

    /* Create session manager (for controls even w/o active audio client) */
    hr = IMMDevice_Activate(sys->dev, &IID_IAudioSessionManager,
                            CLSCTX_ALL, NULL, &pv);
    manager = pv;
    if (SUCCEEDED(hr))
    {
        LPCGUID guid = var_GetBool(aout, "volume-save") ? &GUID_VLC_AUD_OUT : NULL;

        /* Register session control */
        hr = IAudioSessionManager_GetAudioSessionControl(manager, guid, 0,
                                                         &control);
        if (SUCCEEDED(hr))
        {
            char *ua = var_InheritString(aout, "user-agent");
            if (ua != NULL)
            {
                wchar_t *wua = ToWide(ua);
                if (likely(wua != NULL))
                {
                    IAudioSessionControl_SetDisplayName(control, wua, NULL);
                    free(wua);
                }
                free(ua);
            }

            IAudioSessionControl_RegisterAudioSessionNotification(control,
                                                         &sys->session_events);
        }
        else
            msg_Err(aout, "cannot get session control (error 0x%lX)", hr);

        hr = IAudioSessionManager_GetSimpleAudioVolume(manager, guid, FALSE,
                                                       &volume);
        if (FAILED(hr))
            msg_Err(aout, "cannot get simple volume (error 0x%lX)", hr);

        /* Try to get version 2 (Windows 7) of the manager & control */
        wchar_t *siid = NULL;

        hr = IAudioSessionManager_QueryInterface(manager,
                                              &IID_IAudioSessionControl2, &pv);
        if (SUCCEEDED(hr))
        {
            IAudioSessionControl2 *c2 = pv;

            IAudioSessionControl2_SetDuckingPreference(c2, FALSE);
            hr = IAudioSessionControl2_GetSessionInstanceIdentifier(c2, &siid);
            if (FAILED(hr))
                siid = NULL;
            IAudioSessionControl2_Release(c2);
        }
        else
            msg_Dbg(aout, "version 2 session control unavailable");

        hr = IAudioSessionManager_QueryInterface(manager,
                                              &IID_IAudioSessionManager2, &pv);
        if (SUCCEEDED(hr))
        {
            IAudioSessionManager2 *m2 = pv;

            IAudioSessionManager2_RegisterDuckNotification(m2, siid,
                                                           &sys->duck);
            IAudioSessionManager2_Release(m2);
        }
        else
            msg_Dbg(aout, "version 2 session management unavailable");

        CoTaskMemFree(siid);
    }
    else
    {
        msg_Err(aout, "cannot activate session manager (error 0x%lX)", hr);
        control = NULL;
        volume = NULL;
    }

    hr = IMMDevice_Activate(sys->dev, &IID_IAudioEndpointVolume,
                            CLSCTX_ALL, NULL, &pv);
    endpoint = pv;
    if (SUCCEEDED(hr))
    {
        float min, max, inc;

        hr = IAudioEndpointVolume_GetVolumeRange(endpoint, &min, &max, &inc);
        if (SUCCEEDED(hr))
            msg_Dbg(aout, "volume from %+f dB to %+f dB with %f dB increments",
                    min, max, inc);
        else
            msg_Err(aout, "cannot get volume range (error 0x%lX)", hr);
    }
    else
        msg_Err(aout, "cannot activate endpoint volume (error 0x%lX)", hr);

    /* Main loop (adjust volume as long as device is unchanged) */
    while (sys->requested_device == NULL)
    {
        if (volume != NULL)
        {
            float level;

            level = sys->requested_volume;
            if (level >= 0.f)
            {
                hr = ISimpleAudioVolume_SetMasterVolume(volume, level, NULL);
                if (FAILED(hr))
                    msg_Err(aout, "cannot set master volume (error 0x%lX)",
                            hr);
            }
            sys->requested_volume = -1.f;

            hr = ISimpleAudioVolume_GetMasterVolume(volume, &level);
            if (SUCCEEDED(hr))
                aout_VolumeReport(aout, cbrtf(level * sys->gain));
            else
                msg_Err(aout, "cannot get master volume (error 0x%lX)", hr);

            BOOL mute;

            hr = ISimpleAudioVolume_GetMute(volume, &mute);
            if (SUCCEEDED(hr))
                aout_MuteReport(aout, mute != FALSE);
            else
                msg_Err(aout, "cannot get mute (error 0x%lX)", hr);

            if (sys->requested_mute >= 0)
            {
                mute = sys->requested_mute ? TRUE : FALSE;

                hr = ISimpleAudioVolume_SetMute(volume, mute, NULL);
                if (FAILED(hr))
                    msg_Err(aout, "cannot set mute (error 0x%lX)", hr);
            }
            sys->requested_mute = -1;
        }

        SleepConditionVariableCS(&sys->work, &sys->lock, INFINITE);
    }
    LeaveCriticalSection(&sys->lock);

    if (endpoint != NULL)
        IAudioEndpointVolume_Release(endpoint);

    if (manager != NULL)
    {   /* Deregister callbacks *without* the lock */
        hr = IAudioSessionManager_QueryInterface(manager,
                                              &IID_IAudioSessionManager2, &pv);
        if (SUCCEEDED(hr))
        {
            IAudioSessionManager2 *m2 = pv;

            IAudioSessionManager2_UnregisterDuckNotification(m2, &sys->duck);
            IAudioSessionManager2_Release(m2);
        }

        if (volume != NULL)
            ISimpleAudioVolume_Release(volume);

        if (control != NULL)
        {
            IAudioSessionControl_UnregisterAudioSessionNotification(control,
                                                         &sys->session_events);
            IAudioSessionControl_Release(control);
        }

        IAudioSessionManager_Release(manager);
    }

    EnterCriticalSection(&sys->lock);
    IMMDevice_Release(sys->dev);
    sys->dev = NULL;
    return S_OK;
}