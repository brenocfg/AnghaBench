#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  audio_sample_format_t ;
struct TYPE_12__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_13__ {TYPE_4__* stream; int /*<<< orphan*/ * module; int /*<<< orphan*/  client; } ;
typedef  TYPE_3__ aout_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  activate; int /*<<< orphan*/  device; } ;
struct TYPE_14__ {TYPE_1__ owner; } ;
typedef  TYPE_4__ aout_stream_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateDevice ; 
 int /*<<< orphan*/  EnterMTA () ; 
 int /*<<< orphan*/  LeaveMTA () ; 
 int /*<<< orphan*/  aout_stream_Start ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_module_load (TYPE_4__*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* vlc_object_create (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_4__*) ; 

__attribute__((used)) static int Start(audio_output_t *aout, audio_sample_format_t *restrict fmt)
{
    aout_sys_t *sys = aout->sys;
    HRESULT hr;

    aout_stream_t *s = vlc_object_create(aout, sizeof (*s));
    if (unlikely(s == NULL))
        return -1;

    s->owner.device = sys->client;
    s->owner.activate = ActivateDevice;

    EnterMTA();
    sys->module = vlc_module_load(s, "aout stream", NULL, false,
                                  aout_stream_Start, s, fmt, &hr);
    LeaveMTA();

    if (sys->module == NULL)
    {
        vlc_object_delete(s);
        return -1;
    }

    assert (sys->stream == NULL);
    sys->stream = s;
    return 0;
}