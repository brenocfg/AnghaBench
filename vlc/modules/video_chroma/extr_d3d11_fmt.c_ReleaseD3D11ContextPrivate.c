#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ d3d11_video_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_Release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReleaseD3D11ContextPrivate(void *private)
{
    d3d11_video_context_t *octx = private;
    ID3D11DeviceContext_Release(octx->device);
}