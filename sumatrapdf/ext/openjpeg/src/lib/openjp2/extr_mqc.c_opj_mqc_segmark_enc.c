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
typedef  int /*<<< orphan*/  opj_mqc_t ;
typedef  int OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_mqc_encode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  opj_mqc_setcurctx (int /*<<< orphan*/ *,int) ; 

void opj_mqc_segmark_enc(opj_mqc_t *mqc)
{
    OPJ_UINT32 i;
    opj_mqc_setcurctx(mqc, 18);

    for (i = 1; i < 5; i++) {
        opj_mqc_encode(mqc, i % 2);
    }
}