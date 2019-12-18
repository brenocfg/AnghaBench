#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mqc; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int /*<<< orphan*/  opj_mqc_t ;
typedef  int OPJ_UINT32 ;
typedef  int OPJ_INT32 ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_SEGSYM ; 
 int /*<<< orphan*/  T1_CTXNO_UNI ; 
 int /*<<< orphan*/  opj_mqc_decode (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_mqc_setcurctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opj_t1_dec_clnpass_check_segsym(opj_t1_t *t1, OPJ_INT32 cblksty)
{
    if (cblksty & J2K_CCP_CBLKSTY_SEGSYM) {
        opj_mqc_t* mqc = &(t1->mqc);
        OPJ_UINT32 v, v2;
        opj_mqc_setcurctx(mqc, T1_CTXNO_UNI);
        opj_mqc_decode(v, mqc);
        opj_mqc_decode(v2, mqc);
        v = (v << 1) | v2;
        opj_mqc_decode(v2, mqc);
        v = (v << 1) | v2;
        opj_mqc_decode(v2, mqc);
        v = (v << 1) | v2;
        /*
        if (v!=0xa) {
            opj_event_msg(t1->cinfo, EVT_WARNING, "Bad segmentation symbol %x\n", v);
        }
        */
    }
}