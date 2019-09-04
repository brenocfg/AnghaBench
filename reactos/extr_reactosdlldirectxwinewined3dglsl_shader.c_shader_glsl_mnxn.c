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
typedef  int /*<<< orphan*/  tmp_ins ;
struct TYPE_8__ {TYPE_3__* idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct wined3d_shader_src_param {TYPE_4__ reg; TYPE_2__ member_0; } ;
struct wined3d_shader_instruction {int dst_count; int src_count; int handler_idx; struct wined3d_shader_src_param* src; struct wined3d_shader_dst_param* dst; int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct wined3d_shader_dst_param {int write_mask; TYPE_1__ member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 void* WINED3DSIH_DP3 ; 
 void* WINED3DSIH_DP4 ; 
#define  WINED3DSIH_M3x2 132 
#define  WINED3DSIH_M3x3 131 
#define  WINED3DSIH_M3x4 130 
#define  WINED3DSIH_M4x3 129 
#define  WINED3DSIH_M4x4 128 
 int WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  memset (struct wined3d_shader_instruction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shader_glsl_dot (struct wined3d_shader_instruction*) ; 

__attribute__((used)) static void shader_glsl_mnxn(const struct wined3d_shader_instruction *ins)
{
    int i;
    int nComponents = 0;
    struct wined3d_shader_dst_param tmp_dst = {{0}};
    struct wined3d_shader_src_param tmp_src[2] = {{{0}}};
    struct wined3d_shader_instruction tmp_ins;

    memset(&tmp_ins, 0, sizeof(tmp_ins));

    /* Set constants for the temporary argument */
    tmp_ins.ctx = ins->ctx;
    tmp_ins.dst_count = 1;
    tmp_ins.dst = &tmp_dst;
    tmp_ins.src_count = 2;
    tmp_ins.src = tmp_src;

    switch(ins->handler_idx)
    {
        case WINED3DSIH_M4x4:
            nComponents = 4;
            tmp_ins.handler_idx = WINED3DSIH_DP4;
            break;
        case WINED3DSIH_M4x3:
            nComponents = 3;
            tmp_ins.handler_idx = WINED3DSIH_DP4;
            break;
        case WINED3DSIH_M3x4:
            nComponents = 4;
            tmp_ins.handler_idx = WINED3DSIH_DP3;
            break;
        case WINED3DSIH_M3x3:
            nComponents = 3;
            tmp_ins.handler_idx = WINED3DSIH_DP3;
            break;
        case WINED3DSIH_M3x2:
            nComponents = 2;
            tmp_ins.handler_idx = WINED3DSIH_DP3;
            break;
        default:
            break;
    }

    tmp_dst = ins->dst[0];
    tmp_src[0] = ins->src[0];
    tmp_src[1] = ins->src[1];
    for (i = 0; i < nComponents; ++i)
    {
        tmp_dst.write_mask = WINED3DSP_WRITEMASK_0 << i;
        shader_glsl_dot(&tmp_ins);
        ++tmp_src[1].reg.idx[0].offset;
    }
}