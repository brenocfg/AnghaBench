#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* generate_csc_matrix ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpProcamp ;
typedef  int /*<<< orphan*/  VdpColorStandard ;
typedef  int /*<<< orphan*/  VdpCSCMatrix ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERATE_CSC_MATRIX ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

VdpStatus vdp_generate_csc_matrix(const vdp_t *vdp, const VdpProcamp *procamp,
    VdpColorStandard standard, VdpCSCMatrix *csc_matrix)
{
    VdpProcamp buf, *copy = NULL;

    if (procamp != NULL)
    {
        buf = *procamp;
        copy = &buf;
    }
    CHECK_FUNC(GENERATE_CSC_MATRIX);
    return vdp->vt.generate_csc_matrix(copy, standard, csc_matrix);
}