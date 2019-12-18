#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ct; int c; int* bp; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  scalar_t__ OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_mqc_byteout (TYPE_1__*) ; 

void opj_mqc_erterm_enc(opj_mqc_t *mqc)
{
    OPJ_INT32 k = (OPJ_INT32)(11 - mqc->ct + 1);

    while (k > 0) {
        mqc->c <<= mqc->ct;
        mqc->ct = 0;
        opj_mqc_byteout(mqc);
        k -= (OPJ_INT32)mqc->ct;
    }

    if (*mqc->bp != 0xff) {
        opj_mqc_byteout(mqc);
    }
}