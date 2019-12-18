#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_5__ {int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnterMTA () ; 
 int /*<<< orphan*/  LeaveMTA () ; 
 int /*<<< orphan*/  aout_stream_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Stop(audio_output_t *aout)
{
    aout_sys_t *sys = aout->sys;

    assert (sys->stream != NULL);

    EnterMTA();
    aout_stream_Stop(sys->stream);
    LeaveMTA();

    vlc_object_delete(sys->stream);
    sys->stream = NULL;
}