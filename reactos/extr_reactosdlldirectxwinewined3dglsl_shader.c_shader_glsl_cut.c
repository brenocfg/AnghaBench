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
struct wined3d_shader_instruction {scalar_t__ handler_idx; TYPE_4__* ctx; TYPE_3__* src; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_6__ {TYPE_1__* idx; } ;
struct TYPE_7__ {TYPE_2__ reg; } ;
struct TYPE_5__ {unsigned int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
 scalar_t__ WINED3DSIH_CUT ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void shader_glsl_cut(const struct wined3d_shader_instruction *ins)
{
    unsigned int stream = ins->handler_idx == WINED3DSIH_CUT ? 0 : ins->src[0].reg.idx[0].offset;

    if (!stream)
        shader_addline(ins->ctx->buffer, "EndPrimitive();\n");
    else
        FIXME("Unhandled primitive stream %u.\n", stream);
}