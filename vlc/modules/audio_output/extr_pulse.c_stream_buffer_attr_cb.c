#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_3__ {int /*<<< orphan*/  minreq; int /*<<< orphan*/  prebuf; int /*<<< orphan*/  tlength; int /*<<< orphan*/  maxlength; } ;
typedef  TYPE_1__ pa_buffer_attr ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pa_stream_get_buffer_attr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stream_buffer_attr_cb(pa_stream *s, void *userdata)
{
    audio_output_t *aout = userdata;
    const pa_buffer_attr *pba = pa_stream_get_buffer_attr(s);

    msg_Dbg(aout, "changed buffer metrics: maxlength=%u, tlength=%u, "
            "prebuf=%u, minreq=%u",
            pba->maxlength, pba->tlength, pba->prebuf, pba->minreq);
}