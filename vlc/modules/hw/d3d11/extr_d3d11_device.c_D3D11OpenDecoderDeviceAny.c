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
typedef  int /*<<< orphan*/  vout_window_t ;
typedef  int /*<<< orphan*/  vlc_decoder_device ;

/* Variables and functions */
 int D3D11OpenDecoderDevice (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int D3D11OpenDecoderDeviceAny(vlc_decoder_device *device, vout_window_t *wnd)
{
    return D3D11OpenDecoderDevice(device, true, wnd);
}