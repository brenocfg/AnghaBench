#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum WINED3D_SHADER_INSTRUCTION_HANDLER { ____Placeholder_WINED3D_SHADER_INSTRUCTION_HANDLER } WINED3D_SHADER_INSTRUCTION_HANDLER ;

/* Variables and functions */
#define  WINED3DSIH_M3x2 132 
#define  WINED3DSIH_M3x3 131 
#define  WINED3DSIH_M3x4 130 
#define  WINED3DSIH_M4x3 129 
#define  WINED3DSIH_M4x4 128 

__attribute__((used)) static unsigned int get_instr_extra_regcount(enum WINED3D_SHADER_INSTRUCTION_HANDLER instr, unsigned int param)
{
    switch (instr)
    {
        case WINED3DSIH_M4x4:
        case WINED3DSIH_M3x4:
            return param == 1 ? 3 : 0;

        case WINED3DSIH_M4x3:
        case WINED3DSIH_M3x3:
            return param == 1 ? 2 : 0;

        case WINED3DSIH_M3x2:
            return param == 1 ? 1 : 0;

        default:
            return 0;
    }
}