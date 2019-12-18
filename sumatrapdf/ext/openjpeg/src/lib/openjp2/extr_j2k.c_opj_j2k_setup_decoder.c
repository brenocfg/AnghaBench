#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  m_reduce; int /*<<< orphan*/  m_layer; } ;
struct TYPE_9__ {TYPE_1__ m_dec; } ;
struct TYPE_10__ {int /*<<< orphan*/  max_tiles; int /*<<< orphan*/  exp_comps; int /*<<< orphan*/  correct; TYPE_2__ m_specific_param; } ;
struct TYPE_11__ {int dump_state; TYPE_3__ m_cp; } ;
typedef  TYPE_4__ opj_j2k_t ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  jpwl_max_tiles; int /*<<< orphan*/  jpwl_exp_comps; int /*<<< orphan*/  jpwl_correct; int /*<<< orphan*/  cp_reduce; int /*<<< orphan*/  cp_layer; } ;
typedef  TYPE_5__ opj_dparameters_t ;

/* Variables and functions */
 int OPJ_DPARAMETERS_DUMP_FLAG ; 

void opj_j2k_setup_decoder(opj_j2k_t *j2k, opj_dparameters_t *parameters)
{
    if (j2k && parameters) {
        j2k->m_cp.m_specific_param.m_dec.m_layer = parameters->cp_layer;
        j2k->m_cp.m_specific_param.m_dec.m_reduce = parameters->cp_reduce;

        j2k->dump_state = (parameters->flags & OPJ_DPARAMETERS_DUMP_FLAG);
#ifdef USE_JPWL
        j2k->m_cp.correct = parameters->jpwl_correct;
        j2k->m_cp.exp_comps = parameters->jpwl_exp_comps;
        j2k->m_cp.max_tiles = parameters->jpwl_max_tiles;
#endif /* USE_JPWL */
    }
}