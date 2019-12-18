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
struct TYPE_5__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_4__ {int /*<<< orphan*/  hd3d; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_Destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Direct3D11Destroy(vout_display_t *vd)
{
#if !VLC_WINSTORE_APP
    D3D11_Destroy( &vd->sys->hd3d );
#endif
}