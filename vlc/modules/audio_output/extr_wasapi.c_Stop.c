#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ aout_stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  client; int /*<<< orphan*/  started_state; } ;
typedef  TYPE_2__ aout_stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_Stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetTimer (TYPE_1__*) ; 
 scalar_t__ STARTED_STATE_OK ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void Stop(aout_stream_t *s)
{
    aout_stream_sys_t *sys = s->sys;

    ResetTimer(s);

    if (atomic_load(&sys->started_state) == STARTED_STATE_OK)
        IAudioClient_Stop(sys->client);

    IAudioClient_Release(sys->client);

    free(sys);
}