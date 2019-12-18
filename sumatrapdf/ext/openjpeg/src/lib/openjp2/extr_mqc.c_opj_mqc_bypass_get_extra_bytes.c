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
struct TYPE_3__ {int ct; int* bp; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  int OPJ_UINT32 ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */

OPJ_UINT32 opj_mqc_bypass_get_extra_bytes(opj_mqc_t *mqc, OPJ_BOOL erterm)
{
    return (mqc->ct < 7 ||
            (mqc->ct == 7 && (erterm || mqc->bp[-1] != 0xff))) ? 1 : 0;
}