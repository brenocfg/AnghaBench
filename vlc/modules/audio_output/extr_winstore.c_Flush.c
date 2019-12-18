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
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {int /*<<< orphan*/  stream; int /*<<< orphan*/ * client; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EnterMTA () ; 
 int /*<<< orphan*/  LeaveMTA () ; 
 int /*<<< orphan*/  aout_stream_Flush (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_FromHR (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Flush(audio_output_t *aout)
{
    aout_sys_t *sys = aout->sys;
    if( unlikely( sys->client == NULL ) )
        return;

    EnterMTA();
    HRESULT hr = aout_stream_Flush(sys->stream);
    LeaveMTA();

    vlc_FromHR(aout, hr);
}