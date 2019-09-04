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
struct wined3d_shader_register {int type; int /*<<< orphan*/  immconst_type; TYPE_1__* idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
#define  WINED3DSPR_CONSTBOOL 138 
#define  WINED3DSPR_DEPTHOUT 137 
#define  WINED3DSPR_DEPTHOUTGE 136 
#define  WINED3DSPR_DEPTHOUTLE 135 
#define  WINED3DSPR_IMMCONST 134 
#define  WINED3DSPR_LOOP 133 
#define  WINED3DSPR_MISCTYPE 132 
#define  WINED3DSPR_PREDICATE 131 
#define  WINED3DSPR_PRIMID 130 
#define  WINED3DSPR_RASTOUT 129 
#define  WINED3DSPR_SAMPLEMASK 128 
 int /*<<< orphan*/  WINED3D_IMMCONST_SCALAR ; 

__attribute__((used)) static inline BOOL shader_is_scalar(const struct wined3d_shader_register *reg)
{
    switch (reg->type)
    {
        case WINED3DSPR_RASTOUT:
            /* oFog & oPts */
            if (reg->idx[0].offset)
                return TRUE;
            /* oPos */
            return FALSE;

        case WINED3DSPR_CONSTBOOL:  /* b# */
        case WINED3DSPR_DEPTHOUT:   /* oDepth */
        case WINED3DSPR_DEPTHOUTGE:
        case WINED3DSPR_DEPTHOUTLE:
        case WINED3DSPR_LOOP:       /* aL */
        case WINED3DSPR_PREDICATE:  /* p0 */
        case WINED3DSPR_PRIMID:     /* primID */
        case WINED3DSPR_SAMPLEMASK: /* oMask */
            return TRUE;

        case WINED3DSPR_MISCTYPE:
            switch (reg->idx[0].offset)
            {
                case 0: /* vPos */
                    return FALSE;
                case 1: /* vFace */
                    return TRUE;
                default:
                    return FALSE;
            }

        case WINED3DSPR_IMMCONST:
            return reg->immconst_type == WINED3D_IMMCONST_SCALAR;

        default:
            return FALSE;
    }
}