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
struct texture_stage_op {int carg0; int carg1; int carg2; int aarg0; int aarg1; int aarg2; scalar_t__ cop; scalar_t__ aop; } ;
typedef  int BOOL ;

/* Variables and functions */
 int WINED3DTA_SELECTMASK ; 
 int WINED3DTA_TFACTOR ; 
 scalar_t__ WINED3D_TOP_BLEND_FACTOR_ALPHA ; 

__attribute__((used)) static BOOL op_reads_tfactor(const struct texture_stage_op *op)
{
    return (op->carg0 & WINED3DTA_SELECTMASK) == WINED3DTA_TFACTOR
            || (op->carg1 & WINED3DTA_SELECTMASK) == WINED3DTA_TFACTOR
            || (op->carg2 & WINED3DTA_SELECTMASK) == WINED3DTA_TFACTOR
            || (op->aarg0 & WINED3DTA_SELECTMASK) == WINED3DTA_TFACTOR
            || (op->aarg1 & WINED3DTA_SELECTMASK) == WINED3DTA_TFACTOR
            || (op->aarg2 & WINED3DTA_SELECTMASK) == WINED3DTA_TFACTOR
            || op->cop == WINED3D_TOP_BLEND_FACTOR_ALPHA
            || op->aop == WINED3D_TOP_BLEND_FACTOR_ALPHA;
}