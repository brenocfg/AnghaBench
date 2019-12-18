#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ vlc_decoder_device ;
struct TYPE_9__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* cleanupDeviceCb ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;
struct TYPE_11__ {TYPE_2__ external; int /*<<< orphan*/  hd3d; TYPE_1__ dec_device; } ;
typedef  TYPE_4__ d3d11_decoder_device ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_obj_free (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void D3D11CloseDecoderDevice(vlc_decoder_device *device)
{
    d3d11_decoder_device *sys = device->sys;

    ID3D11DeviceContext_Release(sys->dec_device.device);

    D3D11_Destroy(&sys->hd3d);

    if ( sys->external.cleanupDeviceCb )
        sys->external.cleanupDeviceCb( sys->external.opaque );

    vlc_obj_free( VLC_OBJECT(device), sys );
}