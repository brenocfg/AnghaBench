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
struct TYPE_3__ {struct wined3d_device* device; } ;
struct wined3d_texture {TYPE_2__* sub_resources; TYPE_1__ resource; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct wined3d_bo_address {int /*<<< orphan*/  addr; scalar_t__ buffer_object; } ;
struct TYPE_4__ {unsigned int size; int /*<<< orphan*/  locations; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER ; 
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glBufferSubData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetBufferSubData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_memory (struct wined3d_texture*,unsigned int,struct wined3d_bo_address*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL wined3d_texture_copy_sysmem_location(struct wined3d_texture *texture,
        unsigned int sub_resource_idx, struct wined3d_context *context, DWORD location)
{
    unsigned int size = texture->sub_resources[sub_resource_idx].size;
    struct wined3d_device *device = texture->resource.device;
    const struct wined3d_gl_info *gl_info;
    struct wined3d_bo_address dst, src;

    if (!wined3d_texture_prepare_location(texture, sub_resource_idx, context, location))
        return FALSE;

    wined3d_texture_get_memory(texture, sub_resource_idx, &dst, location);
    wined3d_texture_get_memory(texture, sub_resource_idx, &src,
            texture->sub_resources[sub_resource_idx].locations);

    if (dst.buffer_object)
    {
        context = context_acquire(device, NULL, 0);
        gl_info = context->gl_info;
        GL_EXTCALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, dst.buffer_object));
        GL_EXTCALL(glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, size, src.addr));
        GL_EXTCALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
        checkGLcall("PBO upload");
        context_release(context);
        return TRUE;
    }

    if (src.buffer_object)
    {
        context = context_acquire(device, NULL, 0);
        gl_info = context->gl_info;
        GL_EXTCALL(glBindBuffer(GL_PIXEL_PACK_BUFFER, src.buffer_object));
        GL_EXTCALL(glGetBufferSubData(GL_PIXEL_PACK_BUFFER, 0, size, dst.addr));
        GL_EXTCALL(glBindBuffer(GL_PIXEL_PACK_BUFFER, 0));
        checkGLcall("PBO download");
        context_release(context);
        return TRUE;
    }

    memcpy(dst.addr, src.addr, size);
    return TRUE;
}