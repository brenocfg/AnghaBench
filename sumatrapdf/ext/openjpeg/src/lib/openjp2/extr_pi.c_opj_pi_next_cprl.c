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
struct TYPE_8__ {int pdx; int pdy; scalar_t__ pw; scalar_t__ ph; } ;
typedef  TYPE_2__ opj_pi_resolution_t ;
struct TYPE_7__ {size_t compno0; size_t compno1; scalar_t__ ty0; scalar_t__ tx0; scalar_t__ ty1; scalar_t__ tx1; size_t resno0; size_t resno1; size_t layno0; size_t layno1; } ;
struct TYPE_9__ {size_t compno; size_t dx; size_t dy; scalar_t__ ty0; scalar_t__ tx0; scalar_t__ ty1; scalar_t__ tx1; size_t y; size_t x; size_t resno; size_t precno; size_t layno; size_t step_l; size_t step_r; size_t step_c; size_t step_p; size_t include_size; int* include; TYPE_1__ poc; int /*<<< orphan*/  tp_on; TYPE_4__* comps; scalar_t__ first; } ;
typedef  TYPE_3__ opj_pi_iterator_t ;
struct TYPE_10__ {size_t numresolutions; unsigned int dx; unsigned int dy; TYPE_2__* resolutions; } ;
typedef  TYPE_4__ opj_pi_comp_t ;
typedef  size_t OPJ_UINT32 ;
typedef  size_t OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 size_t INT_MAX ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 unsigned int UINT_MAX ; 
 size_t opj_int_ceildiv (scalar_t__,size_t) ; 
 size_t opj_int_floordivpow2 (size_t,size_t) ; 
 int /*<<< orphan*/  opj_pi_emit_error (TYPE_3__*,char*) ; 
 size_t opj_uint_min (size_t,size_t) ; 

__attribute__((used)) static OPJ_BOOL opj_pi_next_cprl(opj_pi_iterator_t * pi)
{
    opj_pi_comp_t *comp = NULL;
    opj_pi_resolution_t *res = NULL;
    OPJ_UINT32 index = 0;

    if (!pi->first) {
        comp = &pi->comps[pi->compno];
        goto LABEL_SKIP;
    } else {
        pi->first = 0;
    }

    for (pi->compno = pi->poc.compno0; pi->compno < pi->poc.compno1; pi->compno++) {
        OPJ_UINT32 resno;
        comp = &pi->comps[pi->compno];
        pi->dx = 0;
        pi->dy = 0;
        for (resno = 0; resno < comp->numresolutions; resno++) {
            OPJ_UINT32 dx, dy;
            res = &comp->resolutions[resno];
            if (res->pdx + comp->numresolutions - 1 - resno < 32 &&
                    comp->dx <= UINT_MAX / (1u << (res->pdx + comp->numresolutions - 1 - resno))) {
                dx = comp->dx * (1u << (res->pdx + comp->numresolutions - 1 - resno));
                pi->dx = !pi->dx ? dx : opj_uint_min(pi->dx, dx);
            }
            if (res->pdy + comp->numresolutions - 1 - resno < 32 &&
                    comp->dy <= UINT_MAX / (1u << (res->pdy + comp->numresolutions - 1 - resno))) {
                dy = comp->dy * (1u << (res->pdy + comp->numresolutions - 1 - resno));
                pi->dy = !pi->dy ? dy : opj_uint_min(pi->dy, dy);
            }
        }
        if (pi->dx == 0 || pi->dy == 0) {
            return OPJ_FALSE;
        }
        if (!pi->tp_on) {
            pi->poc.ty0 = pi->ty0;
            pi->poc.tx0 = pi->tx0;
            pi->poc.ty1 = pi->ty1;
            pi->poc.tx1 = pi->tx1;
        }
        for (pi->y = pi->poc.ty0; pi->y < pi->poc.ty1;
                pi->y += (OPJ_INT32)(pi->dy - (OPJ_UINT32)(pi->y % (OPJ_INT32)pi->dy))) {
            for (pi->x = pi->poc.tx0; pi->x < pi->poc.tx1;
                    pi->x += (OPJ_INT32)(pi->dx - (OPJ_UINT32)(pi->x % (OPJ_INT32)pi->dx))) {
                for (pi->resno = pi->poc.resno0;
                        pi->resno < opj_uint_min(pi->poc.resno1, comp->numresolutions); pi->resno++) {
                    OPJ_UINT32 levelno;
                    OPJ_INT32 trx0, try0;
                    OPJ_INT32 trx1, try1;
                    OPJ_UINT32 rpx, rpy;
                    OPJ_INT32 prci, prcj;
                    res = &comp->resolutions[pi->resno];
                    levelno = comp->numresolutions - 1 - pi->resno;
                    /* Avoids division by zero on id_000004,sig_06,src_000679,op_arith8,pos_49,val_-17 */
                    /* of  https://github.com/uclouvain/openjpeg/issues/938 */
                    if (levelno >= 32 ||
                            ((comp->dx << levelno) >> levelno) != comp->dx ||
                            ((comp->dy << levelno) >> levelno) != comp->dy) {
                        continue;
                    }
                    if ((comp->dx << levelno) > INT_MAX ||
                            (comp->dy << levelno) > INT_MAX) {
                        continue;
                    }
                    trx0 = opj_int_ceildiv(pi->tx0, (OPJ_INT32)(comp->dx << levelno));
                    try0 = opj_int_ceildiv(pi->ty0, (OPJ_INT32)(comp->dy << levelno));
                    trx1 = opj_int_ceildiv(pi->tx1, (OPJ_INT32)(comp->dx << levelno));
                    try1 = opj_int_ceildiv(pi->ty1, (OPJ_INT32)(comp->dy << levelno));
                    rpx = res->pdx + levelno;
                    rpy = res->pdy + levelno;

                    /* To avoid divisions by zero / undefined behaviour on shift */
                    /* in below tests */
                    /* Fixes reading id:000019,sig:08,src:001098,op:flip1,pos:49 */
                    /* of https://github.com/uclouvain/openjpeg/issues/938 */
                    if (rpx >= 31 || ((comp->dx << rpx) >> rpx) != comp->dx ||
                            rpy >= 31 || ((comp->dy << rpy) >> rpy) != comp->dy) {
                        continue;
                    }

                    /* See ISO-15441. B.12.1.5 Component-position-resolution level-layer progression */
                    if (!((pi->y % (OPJ_INT32)(comp->dy << rpy) == 0) || ((pi->y == pi->ty0) &&
                            ((try0 << levelno) % (1 << rpy))))) {
                        continue;
                    }
                    if (!((pi->x % (OPJ_INT32)(comp->dx << rpx) == 0) || ((pi->x == pi->tx0) &&
                            ((trx0 << levelno) % (1 << rpx))))) {
                        continue;
                    }

                    if ((res->pw == 0) || (res->ph == 0)) {
                        continue;
                    }

                    if ((trx0 == trx1) || (try0 == try1)) {
                        continue;
                    }

                    prci = opj_int_floordivpow2(opj_int_ceildiv(pi->x,
                                                (OPJ_INT32)(comp->dx << levelno)), (OPJ_INT32)res->pdx)
                           - opj_int_floordivpow2(trx0, (OPJ_INT32)res->pdx);
                    prcj = opj_int_floordivpow2(opj_int_ceildiv(pi->y,
                                                (OPJ_INT32)(comp->dy << levelno)), (OPJ_INT32)res->pdy)
                           - opj_int_floordivpow2(try0, (OPJ_INT32)res->pdy);
                    pi->precno = (OPJ_UINT32)(prci + prcj * (OPJ_INT32)res->pw);
                    for (pi->layno = pi->poc.layno0; pi->layno < pi->poc.layno1; pi->layno++) {
                        index = pi->layno * pi->step_l + pi->resno * pi->step_r + pi->compno *
                                pi->step_c + pi->precno * pi->step_p;
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
    }

    return OPJ_FALSE;
}