#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {int** texture_states; TYPE_5__** textures; int /*<<< orphan*/ * transforms; } ;
struct wined3d_matrix {int dummy; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_device {int /*<<< orphan*/  shader_priv; TYPE_4__* shader_backend; } ;
struct TYPE_8__ {unsigned int use_map; TYPE_2__* elements; } ;
struct wined3d_context {unsigned int lastWasPow2Texture; TYPE_3__ stream_info; int /*<<< orphan*/  last_was_rhw; struct wined3d_gl_info* gl_info; struct wined3d_device* device; } ;
struct TYPE_10__ {scalar_t__ pow2_matrix; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* shader_has_ffp_proj_control ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__* format; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ MAX_TEXTURES ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WINED3DFMT_UNKNOWN ; 
 int WINED3DTSS_TCI_PASSTHRU ; 
 unsigned int WINED3D_FFP_TEXCOORD0 ; 
 size_t WINED3D_TSS_TEXCOORD_INDEX ; 
 size_t WINED3D_TSS_TEXTURE_TRANSFORM_FLAGS ; 
 unsigned int WINED3D_TS_TEXTURE0 ; 
 int /*<<< orphan*/  compute_texture_matrix (struct wined3d_gl_info const*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wined3d_matrix*) ; 
 unsigned int min (int,scalar_t__) ; 
 int /*<<< orphan*/  multiply_matrix (struct wined3d_matrix*,struct wined3d_matrix*,struct wined3d_matrix*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_ps (struct wined3d_state const*) ; 

void get_texture_matrix(const struct wined3d_context *context, const struct wined3d_state *state,
        unsigned int tex, struct wined3d_matrix *mat)
{
    const struct wined3d_device *device = context->device;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    BOOL generated = (state->texture_states[tex][WINED3D_TSS_TEXCOORD_INDEX] & 0xffff0000)
            != WINED3DTSS_TCI_PASSTHRU;
    unsigned int coord_idx = min(state->texture_states[tex][WINED3D_TSS_TEXCOORD_INDEX & 0x0000ffff],
            MAX_TEXTURES - 1);

    compute_texture_matrix(gl_info, &state->transforms[WINED3D_TS_TEXTURE0 + tex],
            state->texture_states[tex][WINED3D_TSS_TEXTURE_TRANSFORM_FLAGS],
            generated, context->last_was_rhw,
            context->stream_info.use_map & (1u << (WINED3D_FFP_TEXCOORD0 + coord_idx))
            ? context->stream_info.elements[WINED3D_FFP_TEXCOORD0 + coord_idx].format->id
            : WINED3DFMT_UNKNOWN,
            device->shader_backend->shader_has_ffp_proj_control(device->shader_priv), mat);

    if ((context->lastWasPow2Texture & (1u << tex)) && state->textures[tex])
    {
        if (generated)
            FIXME("Non-power-of-two texture being used with generated texture coords.\n");
        /* NP2 texcoord fixup is implemented for pixelshaders so only enable the
         * fixed-function-pipeline fixup via pow2Matrix when no PS is used. */
        if (!use_ps(state))
        {
            TRACE("Non-power-of-two texture matrix multiply fixup.\n");
            multiply_matrix(mat, mat, (struct wined3d_matrix *)state->textures[tex]->pow2_matrix);
        }
    }
}