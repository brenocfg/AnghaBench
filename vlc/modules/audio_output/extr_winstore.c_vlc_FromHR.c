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
struct TYPE_5__ {int /*<<< orphan*/ * client; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ AUDCLNT_E_DEVICE_INVALIDATED ; 
 scalar_t__ AUDCLNT_E_RESOURCES_INVALIDATED ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vlc_FromHR(audio_output_t *aout, HRESULT hr)
{
    aout_sys_t* sys = aout->sys;
    /* Select the default device (and restart) on unplug */
    if (unlikely(hr == AUDCLNT_E_DEVICE_INVALIDATED ||
                 hr == AUDCLNT_E_RESOURCES_INVALIDATED))
    {
        sys->client = NULL;
    }
    return SUCCEEDED(hr) ? 0 : -1;
}