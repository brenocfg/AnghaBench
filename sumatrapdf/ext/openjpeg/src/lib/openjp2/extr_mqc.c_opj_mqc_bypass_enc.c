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
struct TYPE_3__ {int ct; int* bp; scalar_t__ c; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  int OPJ_UINT32 ;
typedef  int OPJ_BYTE ;

/* Variables and functions */
 int BYPASS_CT_INIT ; 

void opj_mqc_bypass_enc(opj_mqc_t *mqc, OPJ_UINT32 d)
{
    if (mqc->ct == BYPASS_CT_INIT) {
        mqc->ct = 8;
    }
    mqc->ct--;
    mqc->c = mqc->c + (d << mqc->ct);
    if (mqc->ct == 0) {
        *mqc->bp = (OPJ_BYTE)mqc->c;
        mqc->ct = 8;
        /* If the previous byte was 0xff, make sure that the next msb is 0 */
        if (*mqc->bp == 0xff) {
            mqc->ct = 7;
        }
        mqc->bp++;
        mqc->c = 0;
    }
}