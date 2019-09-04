#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_stream_info {TYPE_4__* elements; } ;
struct wined3d_state {int* render_states; } ;
struct wined3d_matrix {float _11; float _21; float _31; float _41; float _12; float _22; float _32; float _42; float _13; float _23; float _33; float _43; float _14; float _24; float _34; float _44; } ;
struct wined3d_context {TYPE_1__* d3d_info; int /*<<< orphan*/  device; } ;
struct TYPE_7__ {int /*<<< orphan*/  const* addr; } ;
struct TYPE_8__ {unsigned int stride; TYPE_3__ data; TYPE_2__* format; } ;
struct TYPE_6__ {int emit_idx; } ;
struct TYPE_5__ {int wined3d_creation_flags; } ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,...) ; 
 size_t WINED3D_FFP_BLENDINDICES ; 
 size_t WINED3D_FFP_BLENDWEIGHT ; 
#define  WINED3D_FFP_EMIT_FLOAT1 135 
#define  WINED3D_FFP_EMIT_FLOAT2 134 
#define  WINED3D_FFP_EMIT_FLOAT3 133 
#define  WINED3D_FFP_EMIT_FLOAT4 132 
 int WINED3D_FFP_EMIT_UBYTE4 ; 
 unsigned int WINED3D_FFP_NORMAL ; 
 unsigned int WINED3D_FFP_POSITION ; 
 int WINED3D_LEGACY_FFP_LIGHTING ; 
 size_t WINED3D_RS_VERTEXBLEND ; 
#define  WINED3D_VBF_0WEIGHTS 131 
#define  WINED3D_VBF_1WEIGHTS 130 
#define  WINED3D_VBF_2WEIGHTS 129 
#define  WINED3D_VBF_3WEIGHTS 128 
 int /*<<< orphan*/  get_modelview_matrix (struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/  const,struct wined3d_matrix*) ; 
 int /*<<< orphan*/  invert_matrix (struct wined3d_matrix*,struct wined3d_matrix*) ; 
 int /*<<< orphan*/  invert_matrix_3d (struct wined3d_matrix*,struct wined3d_matrix*) ; 
 int /*<<< orphan*/  use_indexed_vertex_blending (struct wined3d_state const*,struct wined3d_stream_info const*) ; 
 int /*<<< orphan*/  use_software_vertex_processing (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const BYTE *software_vertex_blending(struct wined3d_context *context,
        const struct wined3d_state *state, const struct wined3d_stream_info *si,
        unsigned int element_idx, unsigned int stride_idx, float *result)
{
#define SI_FORMAT(idx) (si->elements[(idx)].format->emit_idx)
#define SI_PTR(idx1, idx2) (si->elements[(idx1)].data.addr + si->elements[(idx1)].stride * (idx2))

    const float *data = (const float *)SI_PTR(element_idx, stride_idx);
    float vector[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float cur_weight, weight_sum = 0.0f;
    struct wined3d_matrix m;
    const BYTE *blend_index;
    const float *weights;
    int i, num_weights;

    if (element_idx != WINED3D_FFP_POSITION && element_idx != WINED3D_FFP_NORMAL)
        return (BYTE *)data;

    if (!use_indexed_vertex_blending(state, si) || !use_software_vertex_processing(context->device))
        return (BYTE *)data;

    if (!si->elements[WINED3D_FFP_BLENDINDICES].data.addr ||
        !si->elements[WINED3D_FFP_BLENDWEIGHT].data.addr)
    {
        FIXME("no blend indices / weights set\n");
        return (BYTE *)data;
    }

    if (SI_FORMAT(WINED3D_FFP_BLENDINDICES) != WINED3D_FFP_EMIT_UBYTE4)
    {
        FIXME("unsupported blend index format: %u\n", SI_FORMAT(WINED3D_FFP_BLENDINDICES));
        return (BYTE *)data;
    }

    /* FIXME: validate weight format */
    switch (state->render_states[WINED3D_RS_VERTEXBLEND])
    {
        case WINED3D_VBF_0WEIGHTS: num_weights = 0; break;
        case WINED3D_VBF_1WEIGHTS: num_weights = 1; break;
        case WINED3D_VBF_2WEIGHTS: num_weights = 2; break;
        case WINED3D_VBF_3WEIGHTS: num_weights = 3; break;
        default:
            FIXME("unsupported vertex blend render state: %u\n", state->render_states[WINED3D_RS_VERTEXBLEND]);
            return (BYTE *)data;
    }

    switch (SI_FORMAT(element_idx))
    {
        case WINED3D_FFP_EMIT_FLOAT4: vector[3] = data[3];
        case WINED3D_FFP_EMIT_FLOAT3: vector[2] = data[2];
        case WINED3D_FFP_EMIT_FLOAT2: vector[1] = data[1];
        case WINED3D_FFP_EMIT_FLOAT1: vector[0] = data[0]; break;
        default:
            FIXME("unsupported value format: %u\n", SI_FORMAT(element_idx));
            return (BYTE *)data;
    }

    blend_index = SI_PTR(WINED3D_FFP_BLENDINDICES, stride_idx);
    weights = (const float *)SI_PTR(WINED3D_FFP_BLENDWEIGHT, stride_idx);
    result[0] = result[1] = result[2] = result[3] = 0.0f;

    for (i = 0; i < num_weights + 1; i++)
    {
        cur_weight = (i < num_weights) ? weights[i] : 1.0f - weight_sum;
        get_modelview_matrix(context, state, blend_index[i], &m);

        if (element_idx == WINED3D_FFP_POSITION)
        {
            result[0] += cur_weight * (vector[0] * m._11 + vector[1] * m._21 + vector[2] * m._31 + vector[3] * m._41);
            result[1] += cur_weight * (vector[0] * m._12 + vector[1] * m._22 + vector[2] * m._32 + vector[3] * m._42);
            result[2] += cur_weight * (vector[0] * m._13 + vector[1] * m._23 + vector[2] * m._33 + vector[3] * m._43);
            result[3] += cur_weight * (vector[0] * m._14 + vector[1] * m._24 + vector[2] * m._34 + vector[3] * m._44);
        }
        else
        {
            if (context->d3d_info->wined3d_creation_flags & WINED3D_LEGACY_FFP_LIGHTING)
                invert_matrix_3d(&m, &m);
            else
                invert_matrix(&m, &m);

            /* multiply with transposed M */
            result[0] += cur_weight * (vector[0] * m._11 + vector[1] * m._12 + vector[2] * m._13);
            result[1] += cur_weight * (vector[0] * m._21 + vector[1] * m._22 + vector[2] * m._23);
            result[2] += cur_weight * (vector[0] * m._31 + vector[1] * m._32 + vector[2] * m._33);
        }

        weight_sum += weights[i];
    }

#undef SI_FORMAT
#undef SI_PTR

    return (BYTE *)result;
}