#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int access; int usage; TYPE_1__* format; } ;
struct wined3d_texture {int flags; TYPE_2__ resource; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  conv_byte_count; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_PIXEL_BUFFER_OBJECT ; 
 int WINED3DUSAGE_DYNAMIC ; 
 int WINED3D_RESOURCE_ACCESS_CPU ; 
 int WINED3D_TEXTURE_COND_NP2_EMULATED ; 
 int WINED3D_TEXTURE_PIN_SYSMEM ; 

__attribute__((used)) static BOOL wined3d_texture_use_pbo(const struct wined3d_texture *texture, const struct wined3d_gl_info *gl_info)
{
    return !(texture->resource.access & WINED3D_RESOURCE_ACCESS_CPU)
            && texture->resource.usage & WINED3DUSAGE_DYNAMIC
            && gl_info->supported[ARB_PIXEL_BUFFER_OBJECT]
            && !texture->resource.format->conv_byte_count
            && !(texture->flags & (WINED3D_TEXTURE_PIN_SYSMEM | WINED3D_TEXTURE_COND_NP2_EMULATED));
}