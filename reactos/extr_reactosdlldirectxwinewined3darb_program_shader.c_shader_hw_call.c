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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {TYPE_4__* src; TYPE_1__* ctx; } ;
struct TYPE_7__ {TYPE_2__* idx; } ;
struct TYPE_8__ {TYPE_3__ reg; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {struct wined3d_string_buffer* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_hw_call(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    shader_addline(buffer, "CAL l%u;\n", ins->src[0].reg.idx[0].offset);
}