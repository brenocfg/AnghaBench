#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* pocs; } ;
typedef  TYPE_1__ opj_tcp_t ;
struct TYPE_6__ {int /*<<< orphan*/  tyE; int /*<<< orphan*/  ty0_t; int /*<<< orphan*/  txE; int /*<<< orphan*/  tx0_t; int /*<<< orphan*/  prcE; int /*<<< orphan*/  prc_t; int /*<<< orphan*/  prg; int /*<<< orphan*/  layE; int /*<<< orphan*/  lay_t; int /*<<< orphan*/  compE; int /*<<< orphan*/  comp_t; int /*<<< orphan*/  resE; int /*<<< orphan*/  res_t; } ;
typedef  TYPE_2__ opj_poc_t ;
struct TYPE_7__ {TYPE_1__* tcps; } ;
typedef  TYPE_3__ opj_cp_t ;
typedef  size_t OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  int OPJ_CHAR ;
typedef  void* OPJ_BOOL ;

/* Variables and functions */
 void* OPJ_FALSE ; 
#define  OPJ_LRCP 129 
#define  OPJ_RLCP 128 
 void* OPJ_TRUE ; 

__attribute__((used)) static OPJ_BOOL opj_pi_check_next_level(OPJ_INT32 pos,
                                        opj_cp_t *cp,
                                        OPJ_UINT32 tileno,
                                        OPJ_UINT32 pino,
                                        const OPJ_CHAR *prog)
{
    OPJ_INT32 i;
    opj_tcp_t *tcps = &cp->tcps[tileno];
    opj_poc_t *tcp = &tcps->pocs[pino];

    if (pos >= 0) {
        for (i = pos; pos >= 0; i--) {
            switch (prog[i]) {
            case 'R':
                if (tcp->res_t == tcp->resE) {
                    if (opj_pi_check_next_level(pos - 1, cp, tileno, pino, prog)) {
                        return OPJ_TRUE;
                    } else {
                        return OPJ_FALSE;
                    }
                } else {
                    return OPJ_TRUE;
                }
                break;
            case 'C':
                if (tcp->comp_t == tcp->compE) {
                    if (opj_pi_check_next_level(pos - 1, cp, tileno, pino, prog)) {
                        return OPJ_TRUE;
                    } else {
                        return OPJ_FALSE;
                    }
                } else {
                    return OPJ_TRUE;
                }
                break;
            case 'L':
                if (tcp->lay_t == tcp->layE) {
                    if (opj_pi_check_next_level(pos - 1, cp, tileno, pino, prog)) {
                        return OPJ_TRUE;
                    } else {
                        return OPJ_FALSE;
                    }
                } else {
                    return OPJ_TRUE;
                }
                break;
            case 'P':
                switch (tcp->prg) {
                case OPJ_LRCP: /* fall through */
                case OPJ_RLCP:
                    if (tcp->prc_t == tcp->prcE) {
                        if (opj_pi_check_next_level(i - 1, cp, tileno, pino, prog)) {
                            return OPJ_TRUE;
                        } else {
                            return OPJ_FALSE;
                        }
                    } else {
                        return OPJ_TRUE;
                    }
                    break;
                default:
                    if (tcp->tx0_t == tcp->txE) {
                        /*TY*/
                        if (tcp->ty0_t == tcp->tyE) {
                            if (opj_pi_check_next_level(i - 1, cp, tileno, pino, prog)) {
                                return OPJ_TRUE;
                            } else {
                                return OPJ_FALSE;
                            }
                        } else {
                            return OPJ_TRUE;
                        }/*TY*/
                    } else {
                        return OPJ_TRUE;
                    }
                    break;
                }/*end case P*/
            }/*end switch*/
        }/*end for*/
    }/*end if*/
    return OPJ_FALSE;
}