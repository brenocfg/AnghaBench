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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ d3d9_video_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice9_Release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReleaseD3D9ContextPrivate(void *private)
{
    d3d9_video_context_t *octx = private;
    IDirect3DDevice9_Release(octx->dev);
}