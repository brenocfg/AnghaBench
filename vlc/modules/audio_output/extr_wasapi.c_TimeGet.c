#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ aout_stream_t ;
struct TYPE_6__ {scalar_t__ rate; scalar_t__ written; int /*<<< orphan*/  client; int /*<<< orphan*/  started_state; } ;
typedef  TYPE_2__ aout_stream_sys_t ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  IAudioClock ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int CLOCK_FREQ ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ GetQPC () ; 
 int /*<<< orphan*/  IAudioClient_GetService (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAudioClock_GetFrequency (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IAudioClock_GetPosition (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  IAudioClock_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClock ; 
 scalar_t__ STARTED_STATE_OK ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_TICK_FROM_MSFTIME (scalar_t__) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 scalar_t__ vlc_tick_from_frac (scalar_t__,scalar_t__) ; 

__attribute__((used)) static HRESULT TimeGet(aout_stream_t *s, vlc_tick_t *restrict delay)
{
    aout_stream_sys_t *sys = s->sys;
    void *pv;
    UINT64 pos, qpcpos, freq;
    HRESULT hr;

    if (atomic_load(&sys->started_state) != STARTED_STATE_OK)
        return E_FAIL;

    hr = IAudioClient_GetService(sys->client, &IID_IAudioClock, &pv);
    if (FAILED(hr))
    {
        msg_Err(s, "cannot get clock (error 0x%lX)", hr);
        return hr;
    }

    IAudioClock *clock = pv;

    hr = IAudioClock_GetPosition(clock, &pos, &qpcpos);
    if (SUCCEEDED(hr))
        hr = IAudioClock_GetFrequency(clock, &freq);
    IAudioClock_Release(clock);
    if (FAILED(hr))
    {
        msg_Err(s, "cannot get position (error 0x%lX)", hr);
        return hr;
    }

    vlc_tick_t written = vlc_tick_from_frac(sys->written, sys->rate);
    vlc_tick_t tick_pos = vlc_tick_from_frac(pos, freq);

    static_assert((10000000 % CLOCK_FREQ) == 0, "Frequency conversion broken");

    *delay = written - tick_pos
           - VLC_TICK_FROM_MSFTIME(GetQPC() - qpcpos);

    return hr;
}