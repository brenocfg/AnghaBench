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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int D3DSPR_ADDR ; 
 int D3DSPR_ATTROUT ; 
 int D3DSPR_COLOROUT ; 
 int D3DSPR_CONST ; 
 int D3DSPR_INPUT ; 
 int D3DSPR_RASTOUT ; 
 int D3DSPR_SAMPLER ; 
 int D3DSPR_TEMP ; 
 int D3DSPR_TEXCRDOUT ; 
 int D3DSP_REGNUM_MASK ; 
 int D3DSP_REGTYPE_MASK ; 
 int D3DSP_REGTYPE_MASK2 ; 
 int D3DSP_REGTYPE_SHIFT ; 
 int D3DSP_REGTYPE_SHIFT2 ; 
 int D3DSP_SWIZZLE_MASK ; 
 int D3DSP_WRITEMASK_0 ; 
 int D3DSP_WRITEMASK_1 ; 
 int D3DSP_WRITEMASK_2 ; 
 int D3DSP_WRITEMASK_3 ; 
 int D3DSP_WRITEMASK_ALL ; 
 int D3DVS_NOSWIZZLE ; 
 int D3DVS_SWIZZLE_MASK ; 
 int D3DVS_SWIZZLE_SHIFT ; 
 int D3DVS_W_W ; 
 int D3DVS_W_X ; 
 int D3DVS_W_Y ; 
 int D3DVS_W_Z ; 
 int D3DVS_X_W ; 
 int D3DVS_X_X ; 
 int D3DVS_X_Y ; 
 int D3DVS_X_Z ; 
 int D3DVS_Y_W ; 
 int D3DVS_Y_X ; 
 int D3DVS_Y_Y ; 
 int D3DVS_Y_Z ; 
 int D3DVS_Z_W ; 
 int D3DVS_Z_X ; 
 int D3DVS_Z_Y ; 
 int D3DVS_Z_Z ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int add_register(char *buffer, DWORD param, BOOL dst, BOOL ps)
{
    char *buf = buffer;
    DWORD reg_type = ((param & D3DSP_REGTYPE_MASK2) >> D3DSP_REGTYPE_SHIFT2)
                   | ((param & D3DSP_REGTYPE_MASK) >> D3DSP_REGTYPE_SHIFT);
    DWORD reg_num = param & D3DSP_REGNUM_MASK;

    if (reg_type == D3DSPR_INPUT)
        buf += sprintf(buf, "v%d", reg_num);
    else if (reg_type == D3DSPR_CONST)
        buf += sprintf(buf, "c%d", reg_num);
    else if (reg_type == D3DSPR_TEMP)
        buf += sprintf(buf, "r%d", reg_num);
    else if (reg_type == D3DSPR_ADDR)
        buf += sprintf(buf, "%s%d", ps ? "t" : "a", reg_num);
    else if (reg_type == D3DSPR_SAMPLER)
        buf += sprintf(buf, "s%d", reg_num);
    else if (reg_type == D3DSPR_RASTOUT)
        buf += sprintf(buf, "oPos");
    else if (reg_type == D3DSPR_COLOROUT)
        buf += sprintf(buf, "oC%d", reg_num);
    else if (reg_type == D3DSPR_TEXCRDOUT)
        buf += sprintf(buf, "oT%d", reg_num);
    else if (reg_type == D3DSPR_ATTROUT)
        buf += sprintf(buf, "oD%d", reg_num);
    else
        buf += sprintf(buf, "? (%d)", reg_type);

    if (dst)
    {
        if ((param & D3DSP_WRITEMASK_ALL) != D3DSP_WRITEMASK_ALL)
        {
            buf += sprintf(buf, ".%s%s%s%s", param & D3DSP_WRITEMASK_0 ? "x" : "",
                                             param & D3DSP_WRITEMASK_1 ? "y" : "",
                                             param & D3DSP_WRITEMASK_2 ? "z" : "",
                                             param & D3DSP_WRITEMASK_3 ? "w" : "");
        }
    }
    else
    {
        if ((param & D3DVS_SWIZZLE_MASK) != D3DVS_NOSWIZZLE)
        {
            if ( ((param & D3DSP_SWIZZLE_MASK) == (D3DVS_X_X | D3DVS_Y_X | D3DVS_Z_X | D3DVS_W_X)) ||
                 ((param & D3DSP_SWIZZLE_MASK) == (D3DVS_X_Y | D3DVS_Y_Y | D3DVS_Z_Y | D3DVS_W_Y)) ||
                 ((param & D3DSP_SWIZZLE_MASK) == (D3DVS_X_Z | D3DVS_Y_Z | D3DVS_Z_Z | D3DVS_W_Z)) ||
                 ((param & D3DSP_SWIZZLE_MASK) == (D3DVS_X_W | D3DVS_Y_W | D3DVS_Z_W | D3DVS_W_W)) )
                buf += sprintf(buf, ".%c", 'w' + (((param >> D3DVS_SWIZZLE_SHIFT) + 1) & 0x3));
            else
                buf += sprintf(buf, ".%c%c%c%c", 'w' + (((param >> (D3DVS_SWIZZLE_SHIFT+0)) + 1) & 0x3),
                                                 'w' + (((param >> (D3DVS_SWIZZLE_SHIFT+2)) + 1) & 0x3),
                                                 'w' + (((param >> (D3DVS_SWIZZLE_SHIFT+4)) + 1) & 0x3),
                                                 'w' + (((param >> (D3DVS_SWIZZLE_SHIFT+6)) + 1) & 0x3));
        }
    }

    return buf - buffer;
}