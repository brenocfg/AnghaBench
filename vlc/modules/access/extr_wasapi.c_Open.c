#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {char* psz_location; int /*<<< orphan*/ * out; int /*<<< orphan*/  pf_control; int /*<<< orphan*/ * pf_demux; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {int /*<<< orphan*/ ** events; int /*<<< orphan*/ * client; int /*<<< orphan*/ * es; int /*<<< orphan*/ * thread; int /*<<< orphan*/ * ready; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  caching; int /*<<< orphan*/  start_time; } ;
typedef  TYPE_2__ demux_sys_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/ * CreateES (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetClient (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_SetEventHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  Thread ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 uintptr_t _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    demux_t *demux = (demux_t *)obj;
    HRESULT hr;

    if (demux->out == NULL)
        return VLC_EGENERIC;

    if (demux->psz_location != NULL && *demux->psz_location != '\0')
        return VLC_EGENERIC; /* TODO non-default device */

    demux_sys_t *sys = vlc_obj_malloc(obj, sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    sys->client = NULL;
    sys->es = NULL;
    sys->caching = VLC_TICK_FROM_MS( var_InheritInteger(obj, "live-caching") );
    sys->start_time = vlc_tick_now();
    for (unsigned i = 0; i < 2; i++)
        sys->events[i] = NULL;

    for (unsigned i = 0; i < 2; i++) {
        sys->events[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (sys->events[i] == NULL)
            goto error;
    }

    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (unlikely(FAILED(hr))) {
        msg_Err(demux, "cannot initialize COM (error 0x%lX)", hr);
        goto error;
    }

    bool loopback;
    sys->client = GetClient(demux, &loopback);
    if (sys->client == NULL) {
        CoUninitialize();
        goto error;
    }

    sys->es = CreateES(demux, sys->client, loopback, sys->caching,
                       &sys->frame_size);
    if (sys->es == NULL)
        goto error;

    hr = IAudioClient_SetEventHandle(sys->client, sys->events[1]);
    if (FAILED(hr)) {
        msg_Err(demux, "cannot set event handle (error 0x%lX)", hr);
        goto error;
    }

    demux->p_sys = sys;

    sys->ready = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (sys->ready == NULL)
        goto error;

    uintptr_t h = _beginthreadex(NULL, 0, Thread, demux, 0, NULL);
    if (h != 0)
        WaitForSingleObject(sys->ready, INFINITE);
    CloseHandle(sys->ready);

    sys->thread = (HANDLE)h;
    if (sys->thread == NULL)
        goto error;
    CoUninitialize();

    demux->pf_demux = NULL;
    demux->pf_control = Control;
    return VLC_SUCCESS;

error:
    if (sys->es != NULL)
        es_out_Del(demux->out, sys->es);
    if (sys->client != NULL)
    {
        IAudioClient_Release(sys->client);
        CoUninitialize();
    }
    for (unsigned i = 0; i < 2; i++)
        if (sys->events[i] != NULL)
            CloseHandle(sys->events[i]);
    return VLC_ENOMEM;
}