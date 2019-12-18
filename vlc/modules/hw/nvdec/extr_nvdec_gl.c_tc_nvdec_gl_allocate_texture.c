#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_decoder_device ;
struct TYPE_10__ {unsigned int tex_count; int /*<<< orphan*/  tex_target; TYPE_2__* vt; int /*<<< orphan*/  gl; TYPE_1__* texs; TYPE_5__* priv; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_11__ {int /*<<< orphan*/ * cuCtx; } ;
typedef  TYPE_4__ decoder_device_nvdec_t ;
struct TYPE_12__ {int /*<<< orphan*/ * cu_res; int /*<<< orphan*/ * mappedArray; int /*<<< orphan*/ * cuConverterCtx; int /*<<< orphan*/ * device; } ;
typedef  TYPE_5__ converter_sys_t ;
struct TYPE_9__ {scalar_t__ (* GetError ) () ;int /*<<< orphan*/  (* BindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TexImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  type; int /*<<< orphan*/  format; int /*<<< orphan*/  internal; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 int CALL_CUDA (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD ; 
 scalar_t__ GL_NO_ERROR ; 
 TYPE_4__* GetNVDECOpaqueDevice (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  cuCtxPopCurrent ; 
 int /*<<< orphan*/  cuCtxPushCurrent ; 
 int /*<<< orphan*/  cuGraphicsGLRegisterImage ; 
 int /*<<< orphan*/  cuGraphicsMapResources ; 
 int /*<<< orphan*/  cuGraphicsSubResourceGetMappedArray ; 
 int /*<<< orphan*/  cuGraphicsUnmapResources ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 () ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc_nvdec_gl_allocate_texture(const opengl_tex_converter_t *tc, GLuint *textures,
                                const GLsizei *tex_width, const GLsizei *tex_height)
{
    converter_sys_t *p_sys = tc->priv;
    vlc_decoder_device *device = p_sys->device;
    decoder_device_nvdec_t *devsys = GetNVDECOpaqueDevice(device);

    int result;
    result = CALL_CUDA(cuCtxPushCurrent, p_sys->cuConverterCtx ? p_sys->cuConverterCtx : devsys->cuCtx);
    if (result != VLC_SUCCESS)
        return result;

    for (unsigned i = 0; i < tc->tex_count; i++)
    {
        tc->vt->BindTexture(tc->tex_target, textures[i]);
        tc->vt->TexImage2D(tc->tex_target, 0, tc->texs[i].internal,
                           tex_width[i], tex_height[i], 0, tc->texs[i].format,
                           tc->texs[i].type, NULL);
        if (tc->vt->GetError() != GL_NO_ERROR)
        {
            msg_Err(tc->gl, "could not alloc PBO buffers");
            return VLC_EGENERIC;
        }

        result = CALL_CUDA(cuGraphicsGLRegisterImage, &p_sys->cu_res[i], textures[i], tc->tex_target, CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD);

        result = CALL_CUDA(cuGraphicsMapResources, 1, &p_sys->cu_res[i], 0);
        result = CALL_CUDA(cuGraphicsSubResourceGetMappedArray, &p_sys->mappedArray[i], p_sys->cu_res[i], 0, 0);
        result = CALL_CUDA(cuGraphicsUnmapResources, 1, &p_sys->cu_res[i], 0);

        tc->vt->BindTexture(tc->tex_target, 0);
    }

    CALL_CUDA(cuCtxPopCurrent, NULL);
    return result;
}