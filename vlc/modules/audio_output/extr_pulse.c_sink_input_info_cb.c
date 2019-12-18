#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mute; int /*<<< orphan*/  volume; } ;
typedef  TYPE_1__ pa_sink_input_info ;
typedef  int /*<<< orphan*/  pa_context ;
struct TYPE_8__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_9__ {int /*<<< orphan*/  cvolume; } ;
typedef  TYPE_3__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VolumeReport (TYPE_2__*) ; 
 int /*<<< orphan*/  aout_MuteReport (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sink_input_info_cb(pa_context *ctx, const pa_sink_input_info *i,
                               int eol, void *userdata)
{
    audio_output_t *aout = userdata;
    aout_sys_t *sys = aout->sys;

    if (eol)
        return;
    (void) ctx;

    sys->cvolume = i->volume; /* cache volume for balance preservation */
    VolumeReport(aout);
    aout_MuteReport(aout, i->mute);
}