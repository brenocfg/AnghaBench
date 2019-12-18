#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pw; int ph; } ;
typedef  TYPE_2__ opj_pi_resolution_t ;
struct TYPE_7__ {size_t layno0; size_t layno1; size_t resno0; size_t resno1; size_t compno0; size_t compno1; int precno1; size_t precno0; } ;
struct TYPE_9__ {size_t compno; size_t resno; size_t layno; size_t precno; size_t step_l; size_t step_r; size_t step_c; size_t step_p; size_t include_size; int* include; TYPE_1__ poc; int /*<<< orphan*/  tp_on; TYPE_4__* comps; scalar_t__ first; } ;
typedef  TYPE_3__ opj_pi_iterator_t ;
struct TYPE_10__ {size_t numresolutions; TYPE_2__* resolutions; } ;
typedef  TYPE_4__ opj_pi_comp_t ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_pi_emit_error (TYPE_3__*,char*) ; 

__attribute__((used)) static OPJ_BOOL opj_pi_next_lrcp(opj_pi_iterator_t * pi)
{
    opj_pi_comp_t *comp = NULL;
    opj_pi_resolution_t *res = NULL;
    OPJ_UINT32 index = 0;

    if (!pi->first) {
        comp = &pi->comps[pi->compno];
        res = &comp->resolutions[pi->resno];
        goto LABEL_SKIP;
    } else {
        pi->first = 0;
    }

    for (pi->layno = pi->poc.layno0; pi->layno < pi->poc.layno1; pi->layno++) {
        for (pi->resno = pi->poc.resno0; pi->resno < pi->poc.resno1;
                pi->resno++) {
            for (pi->compno = pi->poc.compno0; pi->compno < pi->poc.compno1; pi->compno++) {
                comp = &pi->comps[pi->compno];
                if (pi->resno >= comp->numresolutions) {
                    continue;
                }
                res = &comp->resolutions[pi->resno];
                if (!pi->tp_on) {
                    pi->poc.precno1 = res->pw * res->ph;
                }
                for (pi->precno = pi->poc.precno0; pi->precno < pi->poc.precno1; pi->precno++) {
                    index = pi->layno * pi->step_l + pi->resno * pi->step_r + pi->compno *
                            pi->step_c + pi->precno * pi->step_p;
                    /* Avoids index out of bounds access with */
                    /* id_000098,sig_11,src_005411,op_havoc,rep_2 of */
                    /* https://github.com/uclouvain/openjpeg/issues/938 */
                    /* Not sure if this is the most clever fix. Perhaps */
                    /* include should be resized when a POC arises, or */
                    /* the POC should be rejected */
                    if (index >= pi->include_size) {
                        opj_pi_emit_error(pi, "Invalid access to pi->include");
                        return OPJ_FALSE;
                    }
                    if (!pi->include[index]) {
                        pi->include[index] = 1;
                        return OPJ_TRUE;
                    }
LABEL_SKIP:
                    ;
                }
            }
        }
    }

    return OPJ_FALSE;
}