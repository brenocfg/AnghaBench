#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pa_stream ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_DeviceReport (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 char* pa_stream_get_device_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stream_moved_cb(pa_stream *s, void *userdata)
{
    audio_output_t *aout = userdata;
    const char *name = pa_stream_get_device_name(s);

    msg_Dbg(aout, "connected to sink %s", name);
    aout_DeviceReport(aout, name);
}