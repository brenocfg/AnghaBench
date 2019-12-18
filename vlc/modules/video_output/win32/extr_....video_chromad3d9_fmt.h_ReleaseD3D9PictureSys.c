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
struct TYPE_3__ {int /*<<< orphan*/  dxva2_dll; int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ picture_sys_d3d9_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ReleaseD3D9PictureSys(picture_sys_d3d9_t *p_sys)
{
    IDirect3DSurface9_Release(p_sys->surface);
    FreeLibrary(p_sys->dxva2_dll);
}