#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ct; int /*<<< orphan*/  c; int /*<<< orphan*/  a; int /*<<< orphan*/  curctx; } ;
struct TYPE_5__ {scalar_t__ w; TYPE_2__ mqc; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  TYPE_2__ opj_mqc_t ;
typedef  int /*<<< orphan*/  opj_flag_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_t1_dec_clnpass_step_macro (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opj_t1_dec_clnpass_step(
    opj_t1_t *t1,
    opj_flag_t *flagsp,
    OPJ_INT32 *datap,
    OPJ_INT32 oneplushalf,
    OPJ_UINT32 ci,
    OPJ_UINT32 vsc)
{
    OPJ_UINT32 v;

    opj_mqc_t *mqc = &(t1->mqc);   /* MQC component */
    opj_t1_dec_clnpass_step_macro(OPJ_TRUE, OPJ_FALSE,
                                  *flagsp, flagsp, t1->w + 2U, datap,
                                  0, ci, mqc, mqc->curctx,
                                  v, mqc->a, mqc->c, mqc->ct, oneplushalf, vsc);
}