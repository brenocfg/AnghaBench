#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
typedef  int /*<<< orphan*/  audio_sample_format_t ;
struct TYPE_22__ {int headphones; } ;
struct TYPE_23__ {TYPE_2__ current_sink_info; TYPE_4__* sys; } ;
typedef  TYPE_3__ audio_output_t ;
struct TYPE_24__ {int /*<<< orphan*/  gain; TYPE_5__* stream; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; scalar_t__ request_device_restart; } ;
typedef  TYPE_4__ aout_sys_t ;
struct TYPE_21__ {int /*<<< orphan*/ * device; int /*<<< orphan*/  activate; } ;
struct TYPE_25__ {TYPE_1__ owner; } ;
typedef  TYPE_5__ aout_stream_t ;
struct TYPE_26__ {int uintVal; } ;
typedef  TYPE_6__ PROPVARIANT ;
typedef  int /*<<< orphan*/  IPropertyStore ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int AOUT_FMT_HDMI (int /*<<< orphan*/ *) ; 
 int AOUT_FMT_SPDIF (int /*<<< orphan*/ *) ; 
 scalar_t__ AUDCLNT_E_ALREADY_INITIALIZED ; 
 scalar_t__ AUDCLNT_E_DEVICE_INVALIDATED ; 
 int /*<<< orphan*/  ActivateDevice ; 
 int DeviceRestartLocked (TYPE_3__*) ; 
 int DeviceSelectLocked (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterMTA () ; 
#define  Headphones 132 
#define  Headset 131 
 scalar_t__ IMMDevice_OpenPropertyStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IPropertyStore_GetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  IPropertyStore_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveMTA () ; 
#define  MM_PASSTHROUGH_DISABLED 130 
#define  MM_PASSTHROUGH_ENABLED 129 
#define  MM_PASSTHROUGH_ENABLED_HD 128 
 int /*<<< orphan*/  PKEY_AudioEndpoint_FormFactor ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_6__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_6__*) ; 
 int /*<<< orphan*/  STGM_READ ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  aout_GainRequest (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_stream_Start ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int var_InheritInteger (TYPE_3__*,char*) ; 
 char* var_InheritString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * vlc_module_load (TYPE_5__*,char*,char*,int,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_5__* vlc_object_create (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_5__*) ; 

__attribute__((used)) static int Start(audio_output_t *aout, audio_sample_format_t *restrict fmt)
{
    aout_sys_t *sys = aout->sys;

    const bool b_spdif = AOUT_FMT_SPDIF(fmt);
    const bool b_hdmi = AOUT_FMT_HDMI(fmt);
    if (b_spdif || b_hdmi)
    {
        switch (var_InheritInteger(aout, "mmdevice-passthrough"))
        {
            case MM_PASSTHROUGH_DISABLED:
                return -1;
            case MM_PASSTHROUGH_ENABLED:
                if (b_hdmi)
                    return -1;
                /* falltrough */
            case MM_PASSTHROUGH_ENABLED_HD:
                break;
        }
    }

    aout_stream_t *s = vlc_object_create(aout, sizeof (*s));
    if (unlikely(s == NULL))
        return -1;

    s->owner.activate = ActivateDevice;

    EnterMTA();
    EnterCriticalSection(&sys->lock);

    if ((sys->request_device_restart && DeviceRestartLocked(aout) != 0)
      || sys->dev == NULL)
    {
        /* Error if the device restart failed or if a request previously
         * failed. */
        LeaveCriticalSection(&sys->lock);
        LeaveMTA();
        vlc_object_delete(s);
        return -1;
    }

    module_t *module;

    for (;;)
    {
        char *modlist = var_InheritString(aout, "mmdevice-backend");
        HRESULT hr;
        s->owner.device = sys->dev;

        module = vlc_module_load(s, "aout stream", modlist,
                                 false, aout_stream_Start, s, fmt, &hr);
        free(modlist);

        int ret = -1;
        if (hr == AUDCLNT_E_ALREADY_INITIALIZED)
        {
            /* From MSDN: "If the initial call to Initialize fails, subsequent
             * Initialize calls might fail and return error code
             * E_ALREADY_INITIALIZED, even though the interface has not been
             * initialized. If this occurs, release the IAudioClient interface
             * and obtain a new IAudioClient interface from the MMDevice API
             * before calling Initialize again."
             *
             * Therefore, request to MMThread the same device and try again. */

            ret = DeviceRestartLocked(aout);
        }
        else if (hr == AUDCLNT_E_DEVICE_INVALIDATED)
        {
            /* The audio endpoint device has been unplugged, request to
             * MMThread the default device and try again. */

            ret = DeviceSelectLocked(aout, NULL);
        }
        if (ret != 0)
            break;
    }

    if (module != NULL)
    {
        IPropertyStore *props;
        HRESULT hr = IMMDevice_OpenPropertyStore(sys->dev, STGM_READ, &props);
        if (SUCCEEDED(hr))
        {
            PROPVARIANT v;
            PropVariantInit(&v);
            hr = IPropertyStore_GetValue(props, &PKEY_AudioEndpoint_FormFactor, &v);
            if (SUCCEEDED(hr))
            {
                switch (v.uintVal)
                {
                    case Headphones:
                    case Headset:
                        aout->current_sink_info.headphones = true;
                        break;
                }
                PropVariantClear(&v);
            }
            IPropertyStore_Release(props);
        }
    }

    LeaveCriticalSection(&sys->lock);
    LeaveMTA();

    if (module == NULL)
    {
        vlc_object_delete(s);
        return -1;
    }

    assert (sys->stream == NULL);
    sys->stream = s;
    aout_GainRequest(aout, sys->gain);
    return 0;
}