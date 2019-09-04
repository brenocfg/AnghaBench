#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mmtime ;
struct TYPE_4__ {scalar_t__ wType; } ;
typedef  TYPE_1__ MMTIME ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  LPWAVEFORMATEX ;
typedef  int /*<<< orphan*/  HWAVEOUT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ MMSYSERR_ERROR ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ TIME_BYTES ; 
 scalar_t__ TIME_MIDI ; 
 scalar_t__ TIME_MS ; 
 scalar_t__ TIME_SAMPLES ; 
 scalar_t__ TIME_SMPTE ; 
 scalar_t__ TIME_TICKS ; 
 int /*<<< orphan*/  bytes_to_ms (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytes_to_samples (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ time_to_bytes (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waveOutGetPosition (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  wave_out_error (scalar_t__) ; 
 int /*<<< orphan*/  wave_time_format (scalar_t__) ; 
 int winetest_debug ; 

__attribute__((used)) static void check_position(int device, HWAVEOUT wout, DWORD bytes,
                           LPWAVEFORMATEX pwfx )
{
    MMTIME mmtime;
    MMRESULT rc;
    DWORD returned;

    mmtime.wType = TIME_BYTES;
    rc=waveOutGetPosition(wout, &mmtime, sizeof(mmtime) - 1);
    ok(rc==MMSYSERR_ERROR,
       "waveOutGetPosition(%s): rc=%s\n",dev_name(device),wave_out_error(rc));

    mmtime.wType = TIME_BYTES;
    rc=waveOutGetPosition(wout, &mmtime, sizeof(mmtime) + 1);
    ok(rc==MMSYSERR_NOERROR,
       "waveOutGetPosition(%s): rc=%s\n",dev_name(device),wave_out_error(rc));
    if (mmtime.wType != TIME_BYTES && winetest_debug > 1)
        trace("waveOutGetPosition(%s): TIME_BYTES not supported, returned %s\n",
              dev_name(device),wave_time_format(mmtime.wType));
    returned = time_to_bytes(&mmtime, pwfx);
    ok(returned == bytes, "waveOutGetPosition(%s): returned %d bytes, "
       "should be %d\n", dev_name(device), returned, bytes);

    mmtime.wType = TIME_SAMPLES;
    rc=waveOutGetPosition(wout, &mmtime, sizeof(mmtime));
    ok(rc==MMSYSERR_NOERROR,
       "waveOutGetPosition(%s): rc=%s\n",dev_name(device),wave_out_error(rc));
    if (mmtime.wType != TIME_SAMPLES && winetest_debug > 1)
        trace("waveOutGetPosition(%s): TIME_SAMPLES not supported, "
              "returned %s\n",dev_name(device),wave_time_format(mmtime.wType));
    returned = time_to_bytes(&mmtime, pwfx);
    ok(returned == bytes, "waveOutGetPosition(%s): returned %d samples "
       "(%d bytes), should be %d (%d bytes)\n", dev_name(device),
       bytes_to_samples(returned, pwfx), returned,
       bytes_to_samples(bytes, pwfx), bytes);

    mmtime.wType = TIME_MS;
    rc=waveOutGetPosition(wout, &mmtime, sizeof(mmtime));
    ok(rc==MMSYSERR_NOERROR,
       "waveOutGetPosition(%s): rc=%s\n",dev_name(device),wave_out_error(rc));
    if (mmtime.wType != TIME_MS && winetest_debug > 1)
        trace("waveOutGetPosition(%s): TIME_MS not supported, returned %s\n",
              dev_name(device), wave_time_format(mmtime.wType));
    returned = time_to_bytes(&mmtime, pwfx);
    ok(returned == bytes, "waveOutGetPosition(%s): returned %d ms, "
       "(%d bytes), should be %d (%d bytes)\n", dev_name(device),
       bytes_to_ms(returned, pwfx), returned,
       bytes_to_ms(bytes, pwfx), bytes);

    mmtime.wType = TIME_SMPTE;
    rc=waveOutGetPosition(wout, &mmtime, sizeof(mmtime));
    ok(rc==MMSYSERR_NOERROR,
       "waveOutGetPosition(%s): rc=%s\n",dev_name(device),wave_out_error(rc));
    if (mmtime.wType != TIME_SMPTE && winetest_debug > 1)
        trace("waveOutGetPosition(%s): TIME_SMPTE not supported, returned %s\n",
              dev_name(device),wave_time_format(mmtime.wType));
    returned = time_to_bytes(&mmtime, pwfx);
    ok(returned == bytes, "waveOutGetPosition(%s): SMPTE test failed\n",
       dev_name(device));

    mmtime.wType = TIME_MIDI;
    rc=waveOutGetPosition(wout, &mmtime, sizeof(mmtime));
    ok(rc==MMSYSERR_NOERROR,
       "waveOutGetPosition(%s): rc=%s\n",dev_name(device),wave_out_error(rc));
    if (mmtime.wType != TIME_MIDI && winetest_debug > 1)
        trace("waveOutGetPosition(%s): TIME_MIDI not supported, returned %s\n",
              dev_name(device),wave_time_format(mmtime.wType));
    returned = time_to_bytes(&mmtime, pwfx);
    ok(returned == bytes, "waveOutGetPosition(%s): MIDI test failed\n",
       dev_name(device));

    mmtime.wType = TIME_TICKS;
    rc=waveOutGetPosition(wout, &mmtime, sizeof(mmtime));
    ok(rc==MMSYSERR_NOERROR,
       "waveOutGetPosition(%s): rc=%s\n",dev_name(device),wave_out_error(rc));
    if (mmtime.wType != TIME_TICKS && winetest_debug > 1)
        trace("waveOutGetPosition(%s): TIME_TICKS not supported, returned %s\n",
              dev_name(device),wave_time_format(mmtime.wType));
    returned = time_to_bytes(&mmtime, pwfx);
    ok(returned == bytes, "waveOutGetPosition(%s): TICKS test failed\n",
       dev_name(device));
}