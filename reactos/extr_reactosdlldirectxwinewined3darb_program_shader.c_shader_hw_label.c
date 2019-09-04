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
struct shader_arb_ctx_priv {scalar_t__ target_version; int /*<<< orphan*/  in_main_func; } ;
struct TYPE_6__ {TYPE_3__* idx; } ;
struct TYPE_8__ {TYPE_2__ reg; } ;
struct TYPE_7__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {struct shader_arb_ctx_priv* backend_data; struct wined3d_string_buffer* buffer; } ;

/* Variables and functions */
 scalar_t__ ARB ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_hw_label(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct shader_arb_ctx_priv *priv = ins->ctx->backend_data;

    priv->in_main_func = FALSE;
    /* Call instructions activate the NV extensions, not labels and rets. If there is an uncalled
     * subroutine, don't generate a label that will make GL complain
     */
    if(priv->target_version == ARB) return;

    shader_addline(buffer, "l%u:\n", ins->src[0].reg.idx[0].offset);
}