#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_sm1_opcode_info {scalar_t__ handler_idx; scalar_t__ opcode; scalar_t__ min_version; scalar_t__ max_version; } ;
struct TYPE_2__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct wined3d_sm1_data {struct wined3d_sm1_opcode_info* opcode_table; TYPE_1__ shader_version; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ WINED3DSIH_TABLE_SIZE ; 
 scalar_t__ WINED3D_SHADER_VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WINED3D_SM1_OPCODE_MASK ; 

__attribute__((used)) static const struct wined3d_sm1_opcode_info *shader_get_opcode(const struct wined3d_sm1_data *priv, DWORD token)
{
    DWORD shader_version = WINED3D_SHADER_VERSION(priv->shader_version.major, priv->shader_version.minor);
    const struct wined3d_sm1_opcode_info *opcode_table = priv->opcode_table;
    unsigned int i = 0;

    while (opcode_table[i].handler_idx != WINED3DSIH_TABLE_SIZE)
    {
        if ((token & WINED3D_SM1_OPCODE_MASK) == opcode_table[i].opcode
                && shader_version >= opcode_table[i].min_version
                && (!opcode_table[i].max_version || shader_version <= opcode_table[i].max_version))
        {
            return &opcode_table[i];
        }
        ++i;
    }

    FIXME("Unsupported opcode %#x, token 0x%08x, shader version %#x.\n",
            token & WINED3D_SM1_OPCODE_MASK, token, shader_version);

    return NULL;
}